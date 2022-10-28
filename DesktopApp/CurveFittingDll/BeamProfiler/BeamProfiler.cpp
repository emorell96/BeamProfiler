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
    double amplitude = 1.0;
    double sigma_x = 80;

    double sigma_y = 50;

    double x_0 = 300;
    


    double y_0 = 100;
    

    double theta = 0;
    double offset = 0;

    

    
    std::cout << "Image has " << img.rows << " px by " << img.cols << "px\n";
    imshow("Display window - processed", img);
    

    std::cout << "Loading the image into residuals.";
    int k = waitKey(0);

    

    Eigen::MatrixXd expected;



    cv::cv2eigen(img, expected);

    // imshow("blured", scaled_down);

    expected = (1.0/expected.maxCoeff()) * expected;

    std::cout << "mean " << expected.mean() << std::endl;


    std::cout << "Shape of expected profile: " << expected.rows() << " rows by " << expected.cols() << std::endl;
    std::cout << "Shape of blured profile: " << img.rows << " rows by " << img.cols << std::endl;

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
                //&amplitude,
                &sigma_x,
                &sigma_y,
                &x_0,
                &y_0,
                &theta);

               // &offset);
        }
    }

    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;

    minMaxLoc(img, &minVal, &maxVal, &minLoc, &maxLoc);

    std::cout << "min val: " << minVal << std::endl;
    std::cout << "max val: " << maxVal << std::endl;
    std::cout << "min loc: " << minLoc << std::endl;
    std::cout << "max loc: " << maxLoc << std::endl;

    std::cout << "finished loading the image\n";

    Solver::Options options;
    options.max_num_iterations = 50;
    options.num_threads = 8;

    
    options.trust_region_strategy_type = ceres::LEVENBERG_MARQUARDT;
    //options.dogleg_type = ceres::SUBSPACE_DOGLEG;

    // options.min_linear_solver_iterations = 4;
    //options.initial_trust_region_radius = 1;
    //options.check_gradients = true;
    options.use_inner_iterations = false;
    //options.sparse_linear_algebra_library_type = ceres::EIGEN_;
    options.linear_solver_type = ceres::ITERATIVE_SCHUR;
    options.minimizer_progress_to_stdout = false;
    /*options.function_tolerance = 1e-20;
    options.parameter_tolerance = 1e-20;*/
    
    Solver::Summary summary;

    //bounds

    /*problem.SetParameterLowerBound(&amplitude, 0, 0.8);
    problem.SetParameterUpperBound(&amplitude, 0, 1.3);*/

    problem.SetParameterLowerBound(&sigma_x, 0, 30);
    problem.SetParameterLowerBound(&sigma_y, 0, 30);

    problem.SetParameterUpperBound(&sigma_x, 0, 500);
    problem.SetParameterUpperBound(&sigma_y, 0, 500);

    problem.SetParameterLowerBound(&x_0, 0, 0.0);
    problem.SetParameterLowerBound(&y_0, 0, 0.0);

    problem.SetParameterUpperBound(&x_0, 0, expected.rows());
    problem.SetParameterUpperBound(&y_0, 0, expected.cols());

    /*problem.SetParameterLowerBound(&offset, 0, 0.0);
    problem.SetParameterUpperBound(&offset, 0, 0.01);*/

    Solve(options, &problem, &summary);
    std::cout << summary.FullReport() << "\n";
    std::cout << "Initial sigma_x: " << 80.0 << " sigma_y: " << 50.0 << "\n";
    std::cout << "Final   sigma_x: " << sigma_x << " sigma_y: " << sigma_y << "\n";
    std::cout << "Final   x_0: " << x_0 << " y_0: " << y_0 << "\n";
    std::cout << "Final   amplitude: " << amplitude << " theta: " << theta << "\n";
    std::cout << "Final   offset: " << offset << "\n";

    std::cout << "Parameters in Python format: (" << amplitude << ", " << x_0 << ", " << y_0 << ", " << sigma_x << ", " << sigma_y << ", " << theta << ", " << offset << ")" << std::endl;

    // calculate r^2

    Gaussian2DProfileEigen profile(amplitude, x_0, y_0, sigma_x, sigma_y, theta, offset);
     
    

    

    Eigen::MatrixXd values = profile.Calculate(img.cols, img.rows);

    
    std::cout << "Mean value: " << values.mean() << std::endl;
    
    std::cout << "Max value expected: " << expected.maxCoeff() << std::endl;
 
    

    Mat calculatedImage;
    Mat originalImage;

    double maxValue = values.maxCoeff();

    std::cout << "Max calue: " << maxValue << std::endl;

    values = (values / maxValue);

    cv::eigen2cv(values, calculatedImage);
    cv::eigen2cv(expected, originalImage);

    imshow("fitted", calculatedImage);
    imshow("original", originalImage);

    std::cout << "Shape of calculated profile: " << values.rows() << " rows by " << values.cols() << std::endl;
    

    auto ss_residuals = Eigen::pow(values.array() - expected.array(), 2.0).sum();
    auto ss_tot = Eigen::pow(expected.array() - expected.mean(), 2.0).sum();


    std::cout << "ss_residual is = " << ss_residuals << std::endl;
    //std::cout << expected.array() << std::endl;
    std::cout << "Mean value of expected matrix " << expected.mean() << std::endl;
    std::cout << "ss_tot is = " << ss_tot << std::endl;
    
    std::cout << "R^2 is = " << 1.0 - ss_residuals / ss_tot << std::endl;


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
