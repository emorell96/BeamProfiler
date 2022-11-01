using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BeamProfilerSharp.Models;
internal class ImageInformation : ObservableObject
{
    public SmoothOptions SmoothOptions { get; set; } = new SmoothOptions();
    public ResizeOptions ResizeOptions { get; set; } = new ResizeOptions();
}


