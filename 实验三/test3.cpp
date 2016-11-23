#include "stdafx.h"
#include<iostream>  
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include<vector>
#include"ImageFiltering.h"
#include"MeanFilter.h"
#include <math.h>

using namespace std;
using namespace cv;
int main()
{
	//测试3.2
	Mat img = imread("img/menber5.jpg",1);
	imshow("hh", img);
	MeanFilter meanfilter = MeanFilter();
	Mat output1 = img.clone();
	meanfilter.toMeanFilter(img,output1,10);

	waitKey();
	return 0;
}