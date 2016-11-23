#include "stdafx.h"
#include "MeanFilter.h"
#include<iostream>  
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include<vector>
#include <math.h>

using namespace std;
using namespace cv;

MeanFilter::MeanFilter()
{
}
void MeanFilter::integral(const Mat &input, int *pint){
	int height = input.rows;
	int width = input.cols;
	int step = input.step;
	int nc = input.channels();
	uchar * src = input.data;
	int index = 0,index1 = 0;
	int *colsum  = new int[4];//暂时存储的每一行的该行的像素合
	
	for (int yi = 0; yi<height; yi++) {
		for (int i = 0; i < nc; i++){
			colsum[i] = 0;
		}
		
		for (int xi = 0; xi < width; xi++)
		{
			index = nc*(yi*width + xi);
			if (yi == 0){
				index1 =nc*xi;
			}
			else{
				index1 = nc*((yi - 1)*width + xi);
			}
			for (int i = 0; i < nc; i++){
					
				colsum[i] += src[index+i];
				pint[index + i] = pint[index1 + i] + colsum[i];//s(u,v) = s(u,v-1)+sum(I(1:u,v))
			}	
		}
	}
}

void MeanFilter::toMeanFilter(const Mat &input, Mat &output, int window_size){
	int pxcount = window_size*window_size;
	int inputWidth = input.cols;
	int inputHeight = input.rows;
	uchar *inputData = input.data;
	int nc = input.channels();
	int *pint = new int[input.step*inputHeight];//初始化积分图
	integral(input, pint);//得到积分图
	int w = (window_size - 1) / 2;
	Vec4b pixelo;
	Vec3b pixelo1;
	int sy, sx, sy1, sx1;
	for (int yi = 0; yi < inputHeight; yi++) {
		for (int xi = 0; xi < inputWidth; xi++)
		{
			for (int i = 0; i <nc; i++){
				sy = yi + w;
				sx = xi + w;
				sy1 = yi - w - 1;
				sx1 = xi - w - 1;

				/*边界处理，采取镜像的方式*/
				if (sy>inputHeight - 1){
					sy = 2 * inputHeight - sy - 1;
				}
				if (sx>inputWidth - 1){
					sx = 2 * inputWidth - sx - 1;
				}
				if (sy1 < 0){
					sy1 = -sy1;
				}
				if (sx1 < 0){
					sx1 = -sx1;
				}

				/*得到积分窗口的四个角的像素值*/
				int s1 = pint[nc*(sy*inputWidth + sx) + i];
				int s2 = pint[nc*(sy1*inputWidth + sx1) + i];
				int s3 = pint[nc*(sy1*inputWidth + sx) + i];
				int s4 = pint[nc*(sy*inputWidth + sx1) + i];

				/*对不同通道的函数进行区分处理*/
				if (nc == 3){
					pixelo1[i] = (s1 + s2 - s3 - s4) / pxcount;
				}
				else{
					pixelo[i] = (s1 + s2 - s3 - s4) / pxcount;
				}
				
			}
			if (nc == 1){
				output.at<uchar>(yi, xi) = pixelo[0];
			}
			else if (nc == 3){
				output.at<Vec3b>(yi, xi) = pixelo1;
			}
			else if (nc == 4){
				output.at<Vec4b>(yi, xi) = pixelo;
			}

			
		}
	}
	imshow("showImage", output);
	waitKey();
}




MeanFilter::~MeanFilter(){
}
