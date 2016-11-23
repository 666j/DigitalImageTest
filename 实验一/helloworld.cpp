#include "stdafx.h"
#include<iostream>  
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include<vector>


using namespace std;
using namespace cv;


void mixBg(){
	Mat img = imread("img/a.png", -1);//前景图
	Mat bgimg = imread("img/b.png", -1);//背景图
	
	int originalImgH = img.rows;//
	int originalImgW = img.cols;
	int imageHeight = bgimg.rows;//ROI高度
	int imageWidth = bgimg.cols;//ROI宽度
	Mat outImg(imageHeight, imageWidth, CV_8UC4);//输出图片
	
	uchar* originalImageData = img.data;//前景图数据
	uchar* bgImgData = bgimg.data;//背景图数据
	
	for (int i = 0; i < imageHeight; i++)
	{
		for (int j = 0; j < imageWidth; j++)
		{
			int index = 4 * (i*originalImgW + j);//前景图的像素地址
			int index1 = 3 * (i*imageWidth + j);//背景图的像素地址
			Vec4b pixelo1;
			//alpha混合算法
			double alpha = (double)(originalImageData[index + 3]) / 255;
			pixelo1[0] = originalImageData[index] * alpha + bgImgData[index1] * (1 - alpha);
			pixelo1[1] = originalImageData[index + 1] * alpha + bgImgData[index1 + 1] * (1 - alpha);
			pixelo1[2] = originalImageData[index + 2] * alpha + bgImgData[index1 + 2] * (1 - alpha);
			pixelo1[3] = originalImageData[index + 3] * alpha + bgImgData[index1 + 3] * (1 - alpha);
			outImg.at<Vec4b>(i,j)=pixelo1;
		}
	}
	imshow("showImage",outImg);
	waitKey();

}

void chanelExtract(){
	Mat img = imread("img/a.png", -1);

	int imageHeight = img.rows;
	int imageWidth = img.cols;
	Mat outImg(imageHeight, imageWidth, CV_8UC4);
	uchar* inputImageData = img.data;

	for (int i = 0; i < imageHeight; i++)
	{
		for (int j = 0; j < imageWidth; j++)
		{
			int index = 4 * (i*imageWidth + j);
			Vec4b pixelo;
			pixelo[0] = inputImageData[index + 3];
			pixelo[1] = inputImageData[index + 3];
			pixelo[2] = inputImageData[index + 3];
			pixelo[3] = inputImageData[index + 3];
			outImg.at<Vec4b>(i, j) = pixelo;
		}
	}

	imshow("showImage", outImg);
	waitKey();

}


int main()
{
	
	mixBg();
	chanelExtract();
	return 0;
}

