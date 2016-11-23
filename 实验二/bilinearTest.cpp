#include "stdafx.h"
#include "bilinearTest.h"
#include<iostream>  
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include<vector>
#include <math.h>

bilinearTest::bilinearTest()
{
	
}
float bilinearTest::bilinear(float a, float b, float c, float d, float dx, float dy) {
	float  h1 = a + dx*(b - a);   
	float  h2=c+dx*(d-c);
	return h1+dy*(h2-h1);
} 

Mat& bilinearTest::Scale(const Mat &input,Mat &output, float sx, float sy){
	//输入原图的宽高
	int inputHeight = input.rows;
	int inputWidth = input.cols;
	//输出图像的宽高
	int outputHeight = inputHeight*sy;
	int outputWidth = inputWidth*sx;

	
	Mat output1(outputHeight, outputWidth, CV_8UC3);
	
	uchar *inputData = input.data;
	uchar *outputData = output1.data;

	float srcRow, dy, srcCol, dx;//映射的纵坐标，纵坐标小数数位，横坐标，横坐标小数位
	int ix, iy;//映射的坐标的小数位
	float pa, pb, pc, pd;//映射的上下左右四个点
	for (int row = 0; row < outputHeight; row++){
		srcRow = ((float)row) / sy;
		iy = floor(srcRow);
		dy = srcRow - iy;
		for (int col = 0; col < outputWidth; col++){
			srcCol = ((float)col)/sx;
			ix = floor(srcCol);
			dx = srcCol - ix;
			Vec3b pixelo;
			for (int i = 0; i < 3; i++){
				pa = (float)inputData[3 * (iy*inputWidth + ix)+i];
				pb = (float)inputData[3 * ((iy + 1)*inputWidth + ix)+i];
				pc = (float)inputData[3 * (iy*inputWidth + ix + 1)+i];
				pd = (float)inputData[3 * ((iy + 1)*inputWidth + ix + 1)+i];
				pixelo[i] = bilinear(pa, pb, pc, pd, dx, dy);//映射坐标
			}
			output1.at<Vec3b>(row, col) = pixelo;
			
		}
	}
	output = output1;
	return output;
}

bilinearTest::~bilinearTest()
{

}
