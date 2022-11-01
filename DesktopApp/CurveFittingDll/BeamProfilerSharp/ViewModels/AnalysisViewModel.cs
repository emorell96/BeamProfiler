using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Input;
using BeamProfilerSharp.Core.Services;
using BeamProfilerSharp.Models;
using CommunityToolkit.Mvvm.Input;
using Microsoft.Extensions.DependencyInjection;

namespace BeamProfilerSharp.ViewModels;
internal class AnalysisViewModel : MenuBarViewModel
{
    private readonly IFitService fitService;

    internal AnalysisViewModel() : base()
    {
        RunFitCommand = new AsyncRelayCommand(RunFitAsync);
        fitService = App.Services.GetRequiredService<IFitService>();
    }

    internal FitInformation FitInformation { get; set; } = new FitInformation();
    internal ImageInformation ImageInformation { get; set; } = new ImageInformation();

    internal ObservableFitResults ObservableFitResults { get; set; } = new ObservableFitResults();

    internal ICommand RunFitCommand
    {
        get; set;
    }

    private string? _fitImageSource;

    public string? FitImageSource
    {
        get => _fitImageSource;
        set => SetProperty(ref _fitImageSource, value);
    }


    private async Task RunFitAsync()
    {
        var cancellationSource = new CancellationTokenSource();
        cancellationSource.CancelAfter(20000);
        try
        {
            var results = await fitService.RequestFitAsync(new Core.Models.FitOptions
            {
                FitParameters = new Core.Models.FitParameters
                {
                    SigmaX = new Core.Models.Parameter
                    {
                        HasLowerBound = false,
                        HasUpperBound = false,
                        Value = FitInformation.SigmaX
                    },
                    SigmaY = new Core.Models.Parameter
                    {
                        HasLowerBound = false,
                        HasUpperBound = false,
                        Value = FitInformation.SigmaY
                    },
                    Theta = new Core.Models.Parameter
                    {
                        HasLowerBound = false,
                        HasUpperBound = false,
                        Value = FitInformation.Theta
                    },
                    X0 = new Core.Models.Parameter
                    {
                        HasLowerBound = false,
                        HasUpperBound = false,
                        Value = FitInformation.X_0
                    },
                    Y0 = new Core.Models.Parameter
                    {
                        HasLowerBound = false,
                        HasUpperBound = false,
                        Value = FitInformation.Y_0
                    }
                },
                ImageOptions = new Core.Models.ImageOptions(ImageInformation.SmoothOptions.ToCore(),
                                                        ImageInformation.ResizeOptions.ToCore()),
                FilePath = ImageSource?.Replace(@"\", @"\\")

            });

            if(results is not null)
            {
                ObservableFitResults.SetFitResults(results);
            }
        }
        catch (TaskCanceledException) { }
        
    }
}
