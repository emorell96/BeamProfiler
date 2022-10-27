using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BeamProfilerSharp.Models;

internal class FitInformation : ObservableObject
{
    public double X_0 { get; set; } 
    public double Y_0 { get; set; }
    public double SigmaX { get; set; }
    public double SigmaY { get; set; }
    public double Theta { get; set; }
}
