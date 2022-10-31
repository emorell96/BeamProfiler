using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BeamProfilerSharp.Core.Models;
public class FitParameters
{
    public Parameter X0
    {
        get; set;
    }

    public Parameter Y0
    {
        get; set; 
    }

    public Parameter SigmaX
    {
        get; set;
    }

    public Parameter SigmaY
    {
        get; set;
    }

    public Parameter Theta
    {
        get; set;
    }

}
