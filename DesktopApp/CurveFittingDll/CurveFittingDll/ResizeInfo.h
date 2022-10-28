#pragma once
class ResizeInfo
{
public:
	ResizeInfo(bool resize, double factor) : resize(resize), factor(factor) {};

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

