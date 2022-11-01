using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BeamProfilerSharp.Core.Models;
using CommunityToolkit.Mvvm.ComponentModel;

namespace BeamProfilerSharp.Models;
internal class ObservableFitResults : ObservableObject
{

    internal ObservableFitResults(FitResults fitResults)
    {
        ArgumentNullException.ThrowIfNull(fitResults.FinalParameters);
        ArgumentNullException.ThrowIfNull(fitResults.ImageInformation);

        SetFitResults(fitResults);

        IsSet = true;
    }

    internal ObservableFitResults()
    {
        IsSet = false;
    }

    public void SetFitResults(FitResults fitResults)
    {
        ArgumentNullException.ThrowIfNull(fitResults.FinalParameters);
        ArgumentNullException.ThrowIfNull(fitResults.ImageInformation);

        FitInformation = new FitInformation(fitResults.FinalParameters);
        ImageSizeX = fitResults.ImageInformation.PixelsX;
        ImageSizeY = fitResults.ImageInformation.PixelsY;
        IsSet = true;
        Ellipticity = Math.Min(FitInformation.SigmaY, FitInformation.SigmaX) / Math.Max(FitInformation.SigmaY, FitInformation.SigmaX);
    }

    private FitInformation? fitInformation;
    private int imageSizeX;
    private int imageSizeY;
    private bool isSet;
    private double ellipticity;

    public FitInformation? FitInformation
    {
        get => fitInformation;
        set => SetProperty(ref fitInformation, value);
    }

    public int ImageSizeX
    {
        get => imageSizeX;
        set => SetProperty(ref imageSizeX, value);
    }

    public int ImageSizeY
    {
        get => imageSizeY;
        set => SetProperty(ref imageSizeY, value);
    }

    public bool IsSet
    {
        get => isSet; set => SetProperty(ref isSet, value);
    }

    public double Ellipticity
    {
        get => ellipticity;
        set => SetProperty(ref ellipticity, value);
    }
}
