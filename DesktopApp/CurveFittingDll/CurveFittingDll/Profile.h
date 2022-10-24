#pragma once


#if defined(_MSC_VER)

#define CERES_MSVC_USE_UNDERSCORE_PREFIXED_BESSEL_FUNCTIONS //define this variable to use MSVC compatible bessel functions: see https://ceres-solver-review.googlesource.com/c/ceres-solver/+/7490/2/include/ceres/jet.h#515
//#include <windows.h> //https://github.com/ceres-solver/ceres-solver/issues/718
//#define NOMINMAX // https://blog.csdn.net/c271441/article/details/126262263 solves an issue where std::max is not recognized.
#endif

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <ceres/ceres.h>
#include <glog/logging.h>

struct Gaussian2DResidual
{
	Gaussian2DResidual(double x, double y, double z)
		: x_(x), y_(y), z_(z) {};
	template <typename T>
	bool operator()(const T* const amplitude,
		const T* const sigma_x,
		const T* const sigma_y,
		const T* const x_0,
		const T* const y_0,
		const T* const theta,
		const T* const offset,
		T* residual) const {

		auto a = (cos(theta[0]) * cos(theta[0]) / (2 * sigma_x[0] * sigma_x[0]) + (sin(theta[0]) * sin(theta[0])) / (2 * sigma_y[0] * sigma_y[0]));
		auto b = -(sin(2 * theta[0])) / (4 * sigma_x[0] * sigma_x[0]) + (sin(2 * theta[0])) / (4 * sigma_y[0] * sigma_y[0]);
		auto c = (sin(theta[0]) * sin(theta[0])) / (2 * sigma_x[0] * sigma_x[0]) + (cos(theta[0]) * cos(theta[0])) / (2 * sigma_y[0] * sigma_y[0]);


		residual[0] = offset[0] + amplitude[0] * exp(a * (x_ - x_0[0]) * (x_ - x_0[0]) + 2 * b * (x_ - x_0[0]) * (y_ - y_0[0]) + c * (y_ - y_0[0]) * (y_ - y_0[0]));

		return true;
	}

private:
	const double x_;
	const double y_;
	const double z_;
};



