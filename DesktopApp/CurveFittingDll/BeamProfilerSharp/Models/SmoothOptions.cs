using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BeamProfilerSharp.Models;
internal class SmoothOptions : ObservableObject
{
    private bool smooth = true;
    private int kernelSize = 151;
    private int kernelSigma = 20;

    public bool Smooth
    {
        get => smooth;
        set => SetProperty(ref smooth, value);
    }

    public int KernelSize
    {
        get => kernelSize;
        set => SetProperty(ref kernelSize, value);
    }

    public int KernelSigma
    {
        get => kernelSigma; 
        set => SetProperty(ref kernelSigma, value);
    }

    public Core.Models.SmoothOptions ToCore()
    {

        return new Core.Models.SmoothOptions
        {
            KernelSigma = kernelSigma,
            KernelSize= kernelSize,
            Smooth = smooth
        };
    }
}
