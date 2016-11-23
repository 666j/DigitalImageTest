#pragma once
#include<iostream>  
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include<vector>

using namespace std;
using namespace cv;

class ImgTransform
{
public:
	ImgTransform();
	~ImgTransform();
	Mat transformImg(Mat &input);
	double bilinear(double a, double b, double c, double d, double dx, double dy);
};

