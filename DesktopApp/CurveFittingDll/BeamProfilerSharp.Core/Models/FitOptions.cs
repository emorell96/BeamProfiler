using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BeamProfilerSharp.Core.Models;
public class FitOptions
{
    public FitParameters? FitParameters
    {
        get; set;
    }

    public ImageOptions? ImageOptions
    {
        get; set;
    }

    public string? FilePath
    {
        get; set;
    }
}
