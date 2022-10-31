#pragma once

#define GLOG_NO_ABBREVIATED_SEVERITIES

#include <Eigen/Dense>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//#include <opencv2/core/eigen.hpp>


#include <ceres/ceres.h>
#include <ceres/problem.h>
#include "Profile.h"

#include "FitParameters.h"
#include "ImageHandler.h"

using ceres::Problem;
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Solver;

class BeamProfiler
{
public:
	BeamProfiler(ImageHandler& handler, FitParameters& initialParameters);
	void Calibrate(double sensorSizeX, double sensorSizeY);
	int Fit(int max_iterations = 50);

	FitParameters GetParameters() {
		return fitParameters;
	}

	Solver::Summary GetSummary() {
		return summary;
	}

private:
	ImageHandler handler;
	Problem problem;
	FitParameters fitParameters;
	Solver::Options options;
	Solver::Summary summary;

	double sensorSizeX;
	double sensorSizeY;

	void SetUpProblem(int max_iterations = 50);
};

