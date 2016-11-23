#pragma once
#include<iostream>  
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include<vector>

using namespace std;
using namespace cv;
class bilinearTest
{
public:
	bilinearTest();
	float bilinear(float a, float b, float c, float d, float dx, float dy);
	Mat& Scale(const Mat &input,Mat &output, float sx, float sy);
	~bilinearTest();
};

