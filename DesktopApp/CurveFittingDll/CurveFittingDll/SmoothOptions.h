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
		return kernelSigma;
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SmoothOptions, smooth, kernelSize, kernelSigma)
private:
	bool smooth = true;
	int kernelSize = 81;
	int kernelSigma = 70;
};