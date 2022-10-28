#pragma once
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/eigen.hpp>

using namespace cv;

class ImageInformation
{
public:
	ImageInformation(std::string filePath, int pixelsX, int pixelsY, Mat image) : path(filePath), pixelsX(pixelsX), pixelsY(pixelsY), image(image), initialized(true) {};
	ImageInformation() {}

	Mat GetImage() {
		return image;
	}

	void SetImage(Mat image) {
		this->image = image;
	}
private:
	std::string path;

	int pixelsX;
	int pixelsY;

	Mat image;

	bool initialized = false;
	 
};

