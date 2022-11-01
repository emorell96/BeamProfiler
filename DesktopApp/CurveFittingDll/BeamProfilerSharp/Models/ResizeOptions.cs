using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BeamProfilerSharp.Models;
internal class ResizeOptions : ObservableObject
{
    private bool resize = true;
    private double scaleFactor = 0.25;

    public bool Resize
    {
        get => resize;
        set => SetProperty(ref resize, value);
    }
    public double ScaleFactor
    {
        get => scaleFactor;
        set => SetProperty(ref scaleFactor, value);
    }

    public Core.Models.ResizeOptions ToCore()
    {
        return new Core.Models.ResizeOptions()
        {
            Resize = resize,
            ResizeFactor = scaleFactor
        };
    }
}
