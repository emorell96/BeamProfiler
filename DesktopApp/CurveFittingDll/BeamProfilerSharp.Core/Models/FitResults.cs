using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BeamProfilerSharp.Core.Models;
public class FitResults
{
    public FitParameters? FinalParameters
    {
        get; set;
    }

    public ImageInformation? ProcessedImage
    {
        get; set;
    }

    public ImageInformation? FittedImage
    {
        get; set;
    }
}
