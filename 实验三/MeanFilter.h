#pragma once

#include "stdafx.h"

#include<iostream>  
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include<vector>
#include <math.h>



using namespace std;
using namespace cv;

class MeanFilter
{
public:
	MeanFilter();
	~MeanFilter();
	void integral(const Mat &input,int *pint);
	void toMeanFilter(const Mat &input, Mat &output, int window_size);

};

