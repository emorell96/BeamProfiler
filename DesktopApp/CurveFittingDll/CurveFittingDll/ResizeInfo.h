#pragma once

#include "ResizeOptions.h"

class ResizeInfo
{
public:
	ResizeInfo(bool resize, double factor) : resize(resize), factor(factor) {};
	ResizeInfo(ResizeOptions resizeOptions) {
		resize = resizeOptions.GetResize();
		factor = resizeOptions.GetResizeFactor();

	};

	bool IsResizeRequested() {
		return resize;
	}
	double GetFactor() {
		return factor;
	}
private:
	bool resize;
	double factor;
};

