#pragma once
#include "ImageHandler.h"
class BeamProfiler
{
public:
	BeamProfiler(ImageHandler& handler);
	void Calibrate(double sensorSizeX, double sensorSizeY);
	void Fit();
};

