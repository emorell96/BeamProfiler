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
public:
	Gaussian2DResidual(double x, double y, double z)
		: x_(x), y_(y), z_(z) {};
	
	template <typename T>
	bool operator() (
		//const T* const amplitude,
		const T* const sigma_x,
		const T* const sigma_y,
		const T* const x_0,
		const T* const y_0,
		const T* const theta,
		// const T* const offset,
		T* residual) const {

		T a = (cos(theta[0]) * cos(theta[0]) / (T(2) * sigma_x[0] * sigma_x[0]) + (sin(theta[0]) * sin(theta[0])) / (T(2) * sigma_y[0] * sigma_y[0]));
		T b = -(sin(T(2) * theta[0])) / (T(4) * sigma_x[0] * sigma_x[0]) + (sin(T(2) * theta[0])) / (T(4) * sigma_y[0] * sigma_y[0]);
		T c = (sin(theta[0]) * sin(theta[0])) / (T(2) * sigma_x[0] * sigma_x[0]) + (cos(theta[0]) * cos(theta[0])) / (T(2) * sigma_y[0] * sigma_y[0]);



		residual[0] = z_ /*- offset[0]*/ - /*amplitude[0] **/ exp(T(-1.0) * (a * (x_ - x_0[0]) * (x_ - x_0[0])+ T(2) * b * (x_ - x_0[0]) * (y_ - y_0[0]) + c * (y_ - y_0[0]) * (y_ - y_0[0])));

		return true;
	}

private:
	const double x_;
	const double y_;
	const double z_;
};

struct FastGaussian2DResidual
{
public:
	FastGaussian2DResidual(double x, double y, double z)
		: x_(x), y_(y), z_(z){
		 
	};

	template <typename T>
	bool operator() (
		//const T* const amplitude,
		const T* const sigma_x,
		const T* const sigma_y,
		const T* const x_0,
		const T* const y_0,
		const T* const theta,
		// const T* const offset,
		T* residual) const {

		T sigma_squared = T(2) * sigma_x[0] * sigma_x[0];
		T sin_theta_squared = sin(theta[0]) * sin(theta[0]);
		T cos_theta_squared = cos(theta[0]) * cos(theta[0]);
		T sigma_y_squared = T(2) * sigma_y[0] * sigma_y[0];
		T sin_two_theta = sin(T(2) * theta[0]);

		T a = (cos_theta_squared / (sigma_squared) + (sin_theta_squared) / ( sigma_y_squared));
		T b = -(sin_two_theta) / (T(2) * sigma_squared) + (sin_two_theta) / (T(2) * sigma_y_squared);
		T c = (sin_theta_squared) / (sigma_squared) + (cos_theta_squared) / (sigma_y_squared);



		residual[0] = z_ /*- offset[0]*/ - /*amplitude[0] **/ exp(T(-1.0) * (a * (x_ - x_0[0]) * (x_ - x_0[0]) + T(2) * b * (x_ - x_0[0]) * (y_ - y_0[0]) + c * (y_ - y_0[0]) * (y_ - y_0[0])));

		return true;
	}

private:
	const double x_;
	const double y_;
	const double z_;
};


