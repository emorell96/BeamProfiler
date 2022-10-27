using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using BeamProfilerSharp.Models;
using CommunityToolkit.Mvvm.Input;

namespace BeamProfilerSharp.ViewModels;
internal class AnalysisViewModel : MenuBarViewModel
{
    internal AnalysisViewModel() : base()
    {
        RunFitCommand = new AsyncRelayCommand(RunFitAsync);
    }

    internal FitInformation FitInformation { get; set; } = new FitInformation();
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

    }
}
