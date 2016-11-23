#include "stdafx.h"
#include<iostream>  
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include<vector>
#include"bilinearTest.h"
#include"ImgTransform.h"


using namespace std;
using namespace cv;
int main()
{
	//2.1测试
	Mat img = imread("img/test2.jpg");
	bilinearTest bt = bilinearTest();
	Mat output;
	output = bt.Scale(img, output, 0.2, 0.3);
	imshow("showImage", output);
	//2.2测试
	ImgTransform it = ImgTransform();
	Mat output1 = it.transformImg(img);
	imshow("hh", output1);

	waitKey();
	return 0;
}