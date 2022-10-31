#pragma once
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/eigen.hpp>

// using namespace cv;

class ImageInformation
{
public:
	ImageInformation(std::string filePath, int pixelsX, int pixelsY, cv::Mat image) : path(filePath), pixelsX(pixelsX), pixelsY(pixelsY), image(image), initialized(true) {};
	ImageInformation() : pixelsX(0), pixelsY(0) {}

	cv::Mat GetImage() {
		return image;
	}

	void SetImage(cv::Mat image) {
		this->image = image;
	}
private:
	std::string path;

	int pixelsX = 0;
	int pixelsY = 0;

	cv::Mat image;

	bool initialized = false;
	 
};

