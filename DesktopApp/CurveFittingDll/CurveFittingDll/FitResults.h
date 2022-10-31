#pragma once
#include "FitParameters.h"
#include "ImageInformation.h"

#include "json.hpp"

class FitResults
{
public:
	FitParameters finalParameters;
	ImageInformation imageInformation;

	FitResults() {};

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(FitResults, finalParameters, imageInformation)
};

