#pragma once

#include "json.hpp"

using nlohmann::json;

class Parameter {
public:
    double value = 0;

    Parameter() : hasLowerBound(false), hasUpperBound(false) {}

    Parameter(bool hasLowerBound, bool hasUpperBound, double value = 0, double lowerBound = 0, double upperBound = 0) :
        hasLowerBound(hasLowerBound),
        hasUpperBound(hasUpperBound),
        lowerBound(lowerBound),
        upperBound(upperBound),
        value(value)
        {};

    bool HasLowerBound() {
        return hasLowerBound;
    }

    bool HasUpperBound() {
        return hasUpperBound;
    }

    double GetUpperBound() {
        return upperBound;
    }

    double GetLowerBound() {
        return lowerBound;
    }

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Parameter, hasLowerBound, lowerBound, hasUpperBound, upperBound, value)
private:
    bool hasLowerBound = false;
    double lowerBound = 0;

    bool hasUpperBound = false;
    double upperBound = 0;
};


class FitParameters
{
public:
    FitParameters(Parameter& x0, Parameter& y0, Parameter& sigmaX, Parameter& sigmaY, Parameter& theta)
    {
        this->x0 = x0;
        this->y0 = y0;
        this->sigmaX = sigmaX;
        this->sigmaY = sigmaY;
        this->theta = theta;
    };

    FitParameters() {};

    Parameter sigmaX;
    Parameter sigmaY;

    Parameter x0;
    Parameter y0;

    Parameter theta;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(FitParameters, sigmaX, sigmaY, x0, y0, theta)
};

//void from_json(const json& j, FitParameters& p) {
//    j.at("x0").get_to(p.x0);
//    j.at("y0").get_to(p.y0);
//    j.at("sigmaX").get_to(p.sigmaX);
//    j.at("sigmaY").get_to(p.sigmaY);
//    j.at("theta").get_to(p.theta);
//}