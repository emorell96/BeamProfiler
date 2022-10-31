using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BeamProfilerSharp.Core.Models;
public class ImageOptions
{
    public ImageOptions(SmoothOptions smSmoothOptions, ResizeOptions resResizeOptions)
    {
        SmoothOptions = smSmoothOptions ?? throw new ArgumentNullException(nameof(smSmoothOptions));
        ResizeOptions = resResizeOptions ?? throw new ArgumentNullException(nameof(resResizeOptions));
    }

    public SmoothOptions SmoothOptions
    {
        get; set;
    }

    public ResizeOptions ResizeOptions
    {
        get; set;
    }

}

public class ResizeOptions
{
    public bool Resize
    {
        get; set;
    }
    public double ResizeFactor
    {
        get; set;
    }
}

public class SmoothOptions
{
    public bool Smooth
    {
        get; set;
    }

    public int KernelSize
    {
        get; set;
    }

    public int KernelSigma
    {
        get; set;
    }
}
