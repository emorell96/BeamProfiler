// BeamProfiler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <Eigen/Dense>

#include <iostream>
#include <ceres/problem.h>
#include <Profile.h>



#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/eigen.hpp>
#include <Gaussian2DProfileEigen.h>

#include <ImageHandler.h>
#include <FitParameters.h>
#include <BeamProfiler.h>




using namespace cv;


using ceres::Problem;
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Solver;
using cv::resize;

int main()
{
    std::cout << "Enter the image to analyze\n";
    Problem problem;

    std::string filepath;

    std::getline(std::cin, filepath);

    ImageHandler imageHandler;

    imageHandler.Process(filepath, SmoothInfo(true, 150, 70), ResizeInfo(true, 0.25));

    Mat img = imageHandler.GetImage();
    
   /* Mat img = imread(filepath, IMREAD_GRAYSCALE);

    if (img.empty())
    {
        std::cout << "Could not read the image: " << filepath << std::endl;
        return 1;
    }*/
    //imshow("Display window", img);

    // first values:
    // amplitude = 1.0;
    Parameter sigma_x(false, false, 80.0, 30.0, 500.0);

    Parameter sigma_y(false, false, 50.0, 30.0, 500.0);

    Parameter x_0(false, false, 300.0, 0.0, 600);

    Parameter y_0(false, false, 100.0, 0.0, 600);
    

    Parameter theta(false, false, 0.0);

    FitParameters fitParameters(x_0, y_0, sigma_x, sigma_y, theta);

    

    
    std::cout << "Image has " << img.rows << " px by " << img.cols << "px\n";
    imshow("Display window - processed", img);
    

    std::cout << "Loading the image into residuals.";
    int k = waitKey(0);

    BeamProfiler profiler(imageHandler, fitParameters);

    profiler.Fit();

    //Eigen::MatrixXd expected;



    //cv::cv2eigen(img, expected);

    //// imshow("blured", scaled_down);

    //expected = (1.0/expected.maxCoeff()) * expected;

    //std::cout << "mean " << expected.mean() << std::endl;


    //std::cout << "Shape of expected profile: " << expected.rows() << " rows by " << expected.cols() << std::endl;
    //std::cout << "Shape of blured profile: " << img.rows << " rows by " << img.cols << std::endl;

    //for (int i = 0; i < expected.rows(); i++) {
    //    for (int j = 0; j < expected.cols(); j++) {
    //        CostFunction* cost_function =
    //            new AutoDiffCostFunction<FastGaussian2DResidual, 1, 1, 1, 1, 1, 1>(
    //                new FastGaussian2DResidual(double(j), double(i), expected(i, j)));

    //        /*CostFunction* cost_function =
    //            new ceres::NumericDiffCostFunction<Gaussian2DResidual, ceres::CENTRAL, 1, 1, 1, 1, 1, 1>(
    //                new Gaussian2DResidual(double(j), double(i), expected(i, j)));*/

    //        problem.AddResidualBlock(cost_function,
    //            nullptr,
    //            //&amplitude,
    //            &sigma_x,
    //            &sigma_y,
    //            &x_0,
    //            &y_0,
    //            &theta);

    //           // &offset);
    //    }
    //}

    //double minVal;
    //double maxVal;
    //Point minLoc;
    //Point maxLoc;

    //minMaxLoc(img, &minVal, &maxVal, &minLoc, &maxLoc);

    //std::cout << "min val: " << minVal << std::endl;
    //std::cout << "max val: " << maxVal << std::endl;
    //std::cout << "min loc: " << minLoc << std::endl;
    //std::cout << "max loc: " << maxLoc << std::endl;

    //std::cout << "finished loading the image\n";

    //Solver::Options options;
    //options.max_num_iterations = 50;
    //options.num_threads = 8;

    //
    //options.trust_region_strategy_type = ceres::LEVENBERG_MARQUARDT;
    ////options.dogleg_type = ceres::SUBSPACE_DOGLEG;

    //// options.min_linear_solver_iterations = 4;
    ////options.initial_trust_region_radius = 1;
    ////options.check_gradients = true;
    //options.use_inner_iterations = false;
    ////options.sparse_linear_algebra_library_type = ceres::EIGEN_;
    //options.linear_solver_type = ceres::ITERATIVE_SCHUR;
    //options.minimizer_progress_to_stdout = false;
    ///*options.function_tolerance = 1e-20;
    //options.parameter_tolerance = 1e-20;*/
    //
    //Solver::Summary summary;

    ////bounds

    ///*problem.SetParameterLowerBound(&amplitude, 0, 0.8);
    //problem.SetParameterUpperBound(&amplitude, 0, 1.3);*/

    //problem.SetParameterLowerBound(&sigma_x, 0, 30);
    //problem.SetParameterLowerBound(&sigma_y, 0, 30);

    //problem.SetParameterUpperBound(&sigma_x, 0, 500);
    //problem.SetParameterUpperBound(&sigma_y, 0, 500);

    //problem.SetParameterLowerBound(&x_0, 0, 0.0);
    //problem.SetParameterLowerBound(&y_0, 0, 0.0);

    //problem.SetParameterUpperBound(&x_0, 0, expected.rows());
    //problem.SetParameterUpperBound(&y_0, 0, expected.cols());

    ///*problem.SetParameterLowerBound(&offset, 0, 0.0);
    //problem.SetParameterUpperBound(&offset, 0, 0.01);*/

    //Solve(options, &problem, &summary);

    fitParameters = profiler.GetParameters();

    std::cout << profiler.GetSummary().FullReport() << "\n";
    std::cout << "Initial sigma_x: " << 80.0 << " sigma_y: " << 50.0 << "\n";
    std::cout << "Final   sigma_x: " << fitParameters.sigmaX.value << " sigma_y: " << fitParameters.sigmaY.value << "\n";
    std::cout << "Final   x_0: " << fitParameters.x0.value << " y_0: " << fitParameters.y0.value << "\n";
    std::cout << "Final   amplitude: " << 1 << " theta: " << fitParameters.theta.value << "\n";
    std::cout << "Final   offset: " << 0 << "\n";

    std::cout << "Parameters in Python format: (" << 1 << ", " << fitParameters.x0.value << ", " << fitParameters.y0.value << ", " << fitParameters.sigmaX.value << ", " << fitParameters.sigmaY.value << ", " << fitParameters.theta.value << ", " << 0 << ")" << std::endl;

    // calculate r^2

    Gaussian2DProfileEigen profile(1.0, fitParameters.x0.value, fitParameters.y0.value, fitParameters.sigmaX.value, fitParameters.sigmaY.value, fitParameters.theta.value, 0);
     
    

    

    Eigen::MatrixXd values = profile.Calculate(img.cols, img.rows);
 
    

    Mat calculatedImage;
    //Mat originalImage;

    double maxValue = values.maxCoeff();

    std::cout << "Max calue: " << maxValue << std::endl;

    values = (values / maxValue);
#pragma region R^2 calculation


    cv::eigen2cv(values, calculatedImage);
    //cv::eigen2cv(img, originalImage);

    imshow("fitted", calculatedImage);
    imshow("original", img);

    //std::cout << "Shape of calculated profile: " << values.rows() << " rows by " << values.cols() << std::endl;
    //

    //auto ss_residuals = Eigen::pow(values.array() - expected.array(), 2.0).sum();
    //auto ss_tot = Eigen::pow(expected.array() - expected.mean(), 2.0).sum();


    //std::cout << "ss_residual is = " << ss_residuals << std::endl;
    ////std::cout << expected.array() << std::endl;
    //std::cout << "Mean value of expected matrix " << expected.mean() << std::endl;
    //std::cout << "ss_tot is = " << ss_tot << std::endl;
    //
    //std::cout << "R^2 is = " << 1.0 - ss_residuals / ss_tot << std::endl;
#pragma endregion


    k = waitKey(0); // Wait for a keystroke in the window

    return 0;

    
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
