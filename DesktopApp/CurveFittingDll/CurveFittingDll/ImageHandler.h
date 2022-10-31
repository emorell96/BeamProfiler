#pragma once

#include <Eigen/Dense>

#include "ImageInformation.h"
#include "SmoothInfo.h"
#include "ResizeInfo.h"
#include <string>


#include <iostream>


#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/eigen.hpp>

class ImageHandler
{
private:
	ImageInformation imageInformation;

public:

	ImageHandler(){};
	
	int Open(std::string filepath);
	void Smooth(int kernelSize = 150, int kernelWidth = 70);
	void Scale(float factor);
	void Normalize();

	int Process(std::string imagePath, SmoothInfo smoothInfo, ResizeInfo resizeInfo);

	cv::Mat GetImage();
};

