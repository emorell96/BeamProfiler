#include <Eigen/Dense>

#include "ImageHandler.h"
#include "ResizeInfo.h"
#include "SmoothInfo.h"


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/eigen.hpp>



using namespace cv;
using cv::Mat;

int ImageHandler::Open(std::string filepath)
{
	Mat image = imread(filepath, IMREAD_GRAYSCALE);

	if (image.empty())
	{
		std::cout << "Could not read the image: " << filepath << std::endl;
		return 1;
	}

	imageInformation = ImageInformation(filepath, image.rows, image.cols, image);
	return 0;
}

/// <summary>
/// Smooths an image using a gaussian blur. 
/// The kernel size will be incremented by one if it's not odd since the OpenCv method requires a kernel size which is odd.
/// </summary>
/// <param name="kernelSize"></param>
/// <param name="kernelWidth"></param>
void ImageHandler::Smooth(int kernelSize, int kernelWidth)
{
	Mat image = imageInformation.GetImage();

	// if the kernel size is evdn then increment by one to ensure it's odd.
	if (kernelSize % 2 == 0) {
		kernelSize += 1;
	}

	cv::GaussianBlur(image, image, Size(kernelSize, kernelSize), kernelWidth, kernelWidth);
}

void ImageHandler::Scale(float factor)
{
	Mat image = imageInformation.GetImage();

	Mat scaled;
	resize(image, scaled, Size(), factor, factor);

	imageInformation.SetImage(scaled);
}

void ImageHandler::Normalize()
{
	cv::Mat image = imageInformation.GetImage();
	Eigen::MatrixXd normalized;

	cv::cv2eigen<double>(image, normalized);

	// imshow("blured", scaled_down);

	normalized = (1.0 / normalized.maxCoeff()) * normalized * 255.0;

	cv::eigen2cv(normalized, image);

	imageInformation.SetImage(image);
}

int ImageHandler::Process(std::string imagePath, SmoothInfo smoothInfo, ResizeInfo resizeInfo)
{
	if (Open(imagePath) != 0) {
		return 1;
	}

	if (smoothInfo.IsSmoothRequested()) {
		Smooth(smoothInfo.GetKernelSize(), smoothInfo.GetSigma());
	}
	if (resizeInfo.IsResizeRequested()) {
		Scale(resizeInfo.GetFactor());
	}

	return 0;
}

Mat ImageHandler::GetImage()
{
	return imageInformation.GetImage();
}
