using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Input;

namespace BeamProfilerSharp.ViewModels;
internal class MenuBarViewModel : ObservableObject
{
    internal MenuBarViewModel() 
    {
        OpenFileCommand = new AsyncRelayCommand(OpenFile);

        ExitCommand.ExecuteRequested += Close;
    }

    public StandardUICommand ExitCommand { get; set; } = new StandardUICommand(StandardUICommandKind.Close);
    public ICommand OpenFileCommand { get; set; }

    private string? _imageSource;
    public string? ImageSource
    {
        get => _imageSource;
        set => SetProperty(ref _imageSource, value);
    }

    private void Close(XamlUICommand sender, ExecuteRequestedEventArgs args)
    {
        App.Current.Exit();
            
    }

    private async Task OpenFile()
    {
        var picker = new Windows.Storage.Pickers.FileOpenPicker
        {
            ViewMode = Windows.Storage.Pickers.PickerViewMode.Thumbnail,
            SuggestedStartLocation = Windows.Storage.Pickers.PickerLocationId.PicturesLibrary
        };

        var hwnd = WinRT.Interop.WindowNative.GetWindowHandle(App.Window);
        // Associate the HWND with the file picker
        WinRT.Interop.InitializeWithWindow.Initialize(picker, hwnd);

        

        picker.FileTypeFilter.Add(".jpg");
        picker.FileTypeFilter.Add(".jpeg");
        picker.FileTypeFilter.Add(".png");
        picker.FileTypeFilter.Add(".bmp");

        Windows.Storage.StorageFile file = await picker.PickSingleFileAsync();

        ImageSource = file.Path;
    }
}
