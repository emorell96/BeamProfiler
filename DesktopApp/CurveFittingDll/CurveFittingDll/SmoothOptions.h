#pragma once
#include "json.hpp"

class SmoothOptions
{
public:
	bool GetSmooth() {
		return smooth;
	}

	int GetKernelSize() {
		return kernelSize;
	}

	int GetSigma() {
		return sigma;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SmoothOptions, smooth, kernelSize)
private:
	bool smooth = true;
	int kernelSize = 81;
	int sigma = 70;
};