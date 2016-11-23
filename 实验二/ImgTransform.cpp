#include "stdafx.h"
#include "ImgTransform.h"

#include<iostream>  
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include<vector>
#include <math.h>

ImgTransform::ImgTransform()
{
}

Mat ImgTransform::transformImg(Mat &input){
	//����ԭͼ�Ŀ��
	int inputHeight = input.rows;
	int inputWidth = input.cols;
	Mat output(inputHeight, inputWidth, CV_8UC3);

	uchar *inputData = input.data;

	double y1, dy, x1, dx,x,y;//ӳ��������꣬������С����λ��ӳ������꣬������С��λ��ԭͼ�����꣬ԭͼ������
	int ix, iy;//ӳ��������С��λ
	double pa, pb, pc, pd;//ӳ������������ĸ���
	double r, deg;
	
	for (int row = 1; row <inputHeight; row++){
		for (int col = 1; col <inputWidth; col++){

			//�����һ��
			x1 = (col -0.5*inputWidth) / (0.5*inputWidth);
			y1 = (row-0.5*inputHeight) / (0.5*inputHeight);

			//���ݺ�����ӳ��õ���ԭͼ������
			r = sqrt(x1*x1 + y1*y1);
			deg = pow((1 - r),2);

			if (r >= 1){
				x = x1;
				y = y1;
			}
			else{
				x= x1*cos(deg)-sin(deg)*y1;
				y= sin(deg)*x1 + cos(deg)*y1;
			}
			//ԭͼ�����һ������
			x = (x*0.5*inputWidth)+(0.5*inputWidth);
			y = (y*0.5*inputHeight)+(0.5*inputHeight);

			//�����Բ�ֵ
			ix = floor(x);
			iy = floor(y);
			dx = x- ix;
			dy = y - iy;
		
			Vec3b pixelo;
			for (int i = 0; i < 3; i++){
				pa = (double)inputData[3 * (iy*inputWidth + ix) + i];
				pb = (double)inputData[3 * ((iy + 1)*inputWidth + ix) + i];
				pc = (double)inputData[3 * (iy*inputWidth + ix + 1) + i];
				pd = (double)inputData[3 * ((iy + 1)*inputWidth + ix + 1) + i];
				pixelo[i] = bilinear(pa, pb, pc, pd, dx, dy);//ӳ������
			}
			output.at<Vec3b>(row, col) = pixelo;
			
		}
	}
	
	return output;
}

double ImgTransform:: bilinear(double a, double b, double c, double d, double dx, double dy){
	double  h1 = a + dx*(b - a);
	double  h2 = c + dx*(d - c);
	return h1 + dy*(h2 - h1);
}

ImgTransform::~ImgTransform()
{
}
