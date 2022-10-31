#pragma once
#include "SmoothOptions.h"

class SmoothInfo
{
public:
	SmoothInfo(bool smooth, int kernelSize = 51, int sigma = 51) : smooth(smooth), kernelSize(kernelSize), sigma(sigma) {};
	SmoothInfo(SmoothOptions options) {
		smooth = options.GetSmooth();
		kernelSize = options.GetKernelSize();
		sigma = options.GetSigma();
	};

	bool IsSmoothRequested() {
		return smooth;
	}
	int GetKernelSize() {
		return kernelSize;
	}
	int GetSigma() {
		return sigma;
	}



private:
	bool smooth;
	int kernelSize;
	int sigma;
};

