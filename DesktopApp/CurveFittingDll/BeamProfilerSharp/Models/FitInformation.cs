using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BeamProfilerSharp.Models;

internal class FitInformation : ObservableObject
{
    private double x_0 = 0;
    private double y_0 = 0;
    private double sigmaX = 50;
    private double sigmaY = 50;
    private double theta = 0;

    public double X_0
    {
        get => x_0;
        set => SetProperty(ref x_0, value);
    }
    public double Y_0
    {
        get => y_0;
        set => SetProperty(ref y_0, value);
    }
    public double SigmaX
    {
        get => sigmaX;
        set => SetProperty(ref sigmaX, value);
    }
    public double SigmaY
    {
        get => sigmaY;
        set => SetProperty(ref sigmaY, value);
    }
    public double Theta
    {
        get => theta; 
        set => SetProperty(ref theta, value);
    }
}
