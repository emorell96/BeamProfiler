#include "BeamProfiler.h"

//using namespace cv;

using ceres::Problem;
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Solver;

BeamProfiler::BeamProfiler(ImageHandler& handler, FitParameters& initialParameters)
{
	this->handler = handler;
	this->fitParameters = initialParameters;
}

void BeamProfiler::Calibrate(double sensorSizeX, double sensorSizeY)
{
	this->sensorSizeX = sensorSizeX;
	this->sensorSizeY = sensorSizeY;
}

int BeamProfiler::Fit(int max_iterations)
{
    try
    {
        SetUpProblem(max_iterations);
        Solve(options, &problem, &summary);
    }
    catch (const std::exception&)
    {
        return 1;
    }
    return 0;
}

void BeamProfiler::SetUpProblem(int maxIterations)
{
	Eigen::MatrixXd expected;
	cv::cv2eigen(handler.GetImage(), expected);

	expected = (1.0 / expected.maxCoeff()) * expected;

    for (int i = 0; i < expected.rows(); i++) {
        for (int j = 0; j < expected.cols(); j++) {
            CostFunction* cost_function =
                new AutoDiffCostFunction<FastGaussian2DResidual, 1, 1, 1, 1, 1, 1>(
                    new FastGaussian2DResidual(double(j), double(i), expected(i, j)));

            /*CostFunction* cost_function =
                new ceres::NumericDiffCostFunction<Gaussian2DResidual, ceres::CENTRAL, 1, 1, 1, 1, 1, 1>(
                    new Gaussian2DResidual(double(j), double(i), expected(i, j)));*/
            
            problem.AddResidualBlock(cost_function,
                nullptr,
                &(fitParameters.sigmaX.value),
                &(fitParameters.sigmaY.value),
                &(fitParameters.x0.value),
                &(fitParameters.y0.value),
                &(fitParameters.theta.value));
        }
    }

    options.max_num_iterations = maxIterations;

    options.num_threads = std::thread::hardware_concurrency();

    if (options.num_threads == 0) {
        options.num_threads = 8;
    }


    options.trust_region_strategy_type = ceres::LEVENBERG_MARQUARDT;
    //options.dogleg_type = ceres::SUBSPACE_DOGLEG;
    options.minimizer_progress_to_stdout = true;
    // options.min_linear_solver_iterations = 4;
    //options.initial_trust_region_radius = 1;
    //options.check_gradients = true;
    options.use_inner_iterations = false;
    //options.sparse_linear_algebra_library_type = ceres::EIGEN_;
    options.linear_solver_type = ceres::DENSE_QR;
    //options.minimizer_progress_to_stdout = false;
#pragma region Bounds
    if (fitParameters.sigmaX.HasLowerBound()) {
        problem.SetParameterLowerBound(&fitParameters.sigmaX.value, 0, fitParameters.sigmaX.GetLowerBound());
    }
    if (fitParameters.sigmaX.HasUpperBound()) {
        problem.SetParameterUpperBound(&fitParameters.sigmaX.value, 0, fitParameters.sigmaX.GetUpperBound());
    }

    if (fitParameters.sigmaY.HasLowerBound()) {
        problem.SetParameterLowerBound(&fitParameters.sigmaY.value, 0, fitParameters.sigmaY.GetLowerBound());
    }
    if (fitParameters.sigmaY.HasUpperBound()) {
        problem.SetParameterUpperBound(&fitParameters.sigmaY.value, 0, fitParameters.sigmaY.GetUpperBound());
    }

    if (fitParameters.x0.HasLowerBound()) {
        problem.SetParameterLowerBound(&fitParameters.x0.value, 0, fitParameters.x0.GetLowerBound());
    }
    if (fitParameters.x0.HasUpperBound()) {
        problem.SetParameterLowerBound(&fitParameters.x0.value, 0, fitParameters.x0.GetUpperBound());
    } 

    if (fitParameters.y0.HasLowerBound()) {
        problem.SetParameterLowerBound(&fitParameters.y0.value, 0, fitParameters.y0.GetLowerBound());
    }
    if (fitParameters.y0.HasUpperBound()) {
        problem.SetParameterLowerBound(&fitParameters.y0.value, 0, fitParameters.y0.GetUpperBound());
    }

    if (fitParameters.theta.HasLowerBound()) {
        problem.SetParameterLowerBound(&(fitParameters.theta.value), 0, fitParameters.theta.GetLowerBound());
    }
    if (fitParameters.theta.HasUpperBound()) {
        problem.SetParameterLowerBound(&fitParameters.theta.value, 0, fitParameters.theta.GetUpperBound());
    }
#pragma endregion
}
