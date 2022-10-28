#pragma once

class Parameter {
public:
    double value = 0;

    Parameter() : withLowerBound(false), withUpperBound(false) {}

    Parameter(bool withLowerBound, bool withUpperBound, double value = 0, double lowerBound = 0, double upperBound = 0) :
        withLowerBound(withLowerBound),
        withUpperBound(withUpperBound),
        minValue(lowerBound),
        maxValue(upperBound),
        value(value)
        {};

    bool HasLowerBound() {
        return withLowerBound;
    }

    bool HasUpperBound() {
        return withUpperBound;
    }

    double GetUpperBound() {
        return maxValue;
    }

    double GetLowerBound() {
        return minValue;
    }

private:
    bool withLowerBound = false;
    double minValue = 0;

    bool withUpperBound = false;
    double maxValue = 0;
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
};

