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
        ArgumentNullException.ThrowIfNull(fitResults.FittedImage);
        //ArgumentNullException.ThrowIfNull(fitResults.ProcessedImage);

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
        ArgumentNullException.ThrowIfNull(fitResults.FittedImage);

        FitInformation = new FitInformation(fitResults.FinalParameters);
        ImageSizeX = fitResults.FittedImage.PixelsX;
        ImageSizeY = fitResults.FittedImage.PixelsY;

        FittedImagePath = fitResults.FittedImage.Path?.Replace(@"\\", @"\") ?? "none";
        ProcessedImagePath = fitResults.ProcessedImage?.Path?.Replace(@"\\", @"\") ?? "none";

        IsSet = true;
        Ellipticity = Math.Min(FitInformation.SigmaY, FitInformation.SigmaX) / Math.Max(FitInformation.SigmaY, FitInformation.SigmaX);
    }

    private FitInformation? fitInformation;
    private int imageSizeX;
    private int imageSizeY;
    private bool isSet;
    private double ellipticity;
    private string fittedImagePath = "none";
    private string processedImagePath = "none";

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

    public string FittedImagePath
    {
        get => fittedImagePath;
        set => SetProperty(ref fittedImagePath, value);
    }

    public string ProcessedImagePath
    {
        get => processedImagePath;
        set => SetProperty(ref processedImagePath, value);
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
