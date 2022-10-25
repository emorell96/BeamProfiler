#pragma once
#include <Eigen/Dense>

using Eigen::RowVectorXd;
using Eigen::VectorXd;

class Gaussian2DProfileEigen
{
public:
	Gaussian2DProfileEigen(double amplitude, double x_0, double y_0, double sigma_x, double sigma_y, double theta, double offset) :
		_amplitude(amplitude),
		_x_0(x_0),
		_y_0(y_0),
		_sigma_x(sigma_x),
		_sigma_y(sigma_y),
		_theta(theta),
		_offset(offset) {
		RecalculateCoefficients();
	};

	Eigen::MatrixXd Calculate(int pixels_x, int pixels_y) {

		Eigen::MatrixXd X = RowVectorXd::LinSpaced(pixels_x, 0.0, (double)(pixels_x - 1.0)).replicate(pixels_y, 1);
		Eigen::MatrixXd Y = VectorXd::LinSpaced(pixels_y, 0.0, (double)(pixels_y - 1.0)).replicate(1, pixels_x);

		return _offset + _amplitude * Eigen::exp(-(_a * Eigen::pow(X.array() - _x_0, 2) + 2.0 * _b * (X.array() - _x_0) * (Y.array() - _y_0) + _c * Eigen::pow(Y.array() - _y_0, 2)));
		

	}

	void RecalculateCoefficients() {
		_a = (std::cos(_theta) * std::cos(_theta) / (2.0 * _sigma_x * _sigma_x) + (std::sin(_theta) * std::sin(_theta)) / (2.0 * _sigma_y * _sigma_y));
		_b = -(std::sin(2.0 * _theta)) / (4.0 * _sigma_x * _sigma_x) + (std::sin(2.0 * _theta)) / (4.0 * _sigma_y * _sigma_y);
		_c = (std::sin(_theta) * std::sin(_theta)) / (2.0 * _sigma_x * _sigma_x) + (std::cos(_theta) * std::cos(_theta)) / (2.0 * _sigma_y * _sigma_y);
	}

private:
	double _amplitude;
	double _x_0;
	double _y_0;
	double _sigma_x;
	double _sigma_y;
	double _theta;
	double _offset;

	double _a;
	double _b;
	double _c;
};


