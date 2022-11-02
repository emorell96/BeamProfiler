#pragma once
#include "FitParameters.h"
#include "ImageInformation.h"

#include "json.hpp"

class FitResults
{
public:
	FitParameters finalParameters;
	//ImageInformation imageInformation;
	ImageInformation fittedImage;
	ImageInformation processedImage;

	FitResults() {};

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(FitResults, finalParameters, fittedImage, processedImage)
};

