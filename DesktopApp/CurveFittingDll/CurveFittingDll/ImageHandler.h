#pragma once


#include "ImageInformation.h"
#include "SmoothInfo.h"
#include "ResizeInfo.h"
#include <string>

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

	Mat GetImage();
};

