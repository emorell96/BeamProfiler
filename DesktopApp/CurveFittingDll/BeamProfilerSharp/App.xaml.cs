// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Runtime.InteropServices.WindowsRuntime;
using BeamProfilerSharp.Core.Services;
using BeamProfilerSharp.Services;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.UI;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using Microsoft.UI.Xaml.Shapes;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using WinRT.Interop;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace BeamProfilerSharp;
/// <summary>
/// Provides application-specific behavior to supplement the default Application class.
/// </summary>
public partial class App : Application
{
    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    public App()
    {
        
        this.InitializeComponent();

    }

    /// <summary>
    /// Invoked when the application is launched normally by the end user.  Other entry points
    /// will be used such as when the application is launched to open a specific file.
    /// </summary>
    /// <param name="args">Details about the launch request and process.</param>
    protected override void OnLaunched(Microsoft.UI.Xaml.LaunchActivatedEventArgs args)
    {
        host = Host.CreateDefaultBuilder(args.Arguments.Split(","))
                    .ConfigureServices(ConfigureServices)
                    .Build();

        m_window = new MainWindow();
        
        m_window.Activate();

        var serverService = Services.GetRequiredService<IServerService>();
        serverService.StartServer();

        m_window.Closed += M_window_Closed;

        //host.Run();
    }

    private void M_window_Closed(object sender, WindowEventArgs args)
    {
        if(m_window is not null)
        {
            m_window.Closed -= M_window_Closed;
        }
        // hide the window while we close the background resources (this will just hide the window to the user, making it seem that it closes a lot faster).
        var currentWindow = GetAppWindowForCurrentWindow();
        currentWindow.Hide();


        var serverService = Services.GetRequiredService<IServerService>();
        serverService.StopServerAsync().Wait();

    }

    private void ConfigureServices(HostBuilderContext context, IServiceCollection services)
    {
        services.AddHttpClient<IFitService, FitService>()
            .ConfigurePrimaryHttpMessageHandler(s =>
            {
                return new HttpClientHandler
                {
                    AutomaticDecompression = System.Net.DecompressionMethods.All,
                    Proxy = new WebProxy("http://localhost:5555", false)
                };
            });

        services.AddSingleton<IServerService, ServerService>();  

    }

    private AppWindow GetAppWindowForCurrentWindow()
    {
        IntPtr hWnd = WindowNative.GetWindowHandle(m_window);
        WindowId wndId = Win32Interop.GetWindowIdFromWindow(hWnd);
        return AppWindow.GetFromWindowId(wndId);
    }


    private static Window? m_window;

    public static IHost? host;

    public static IServiceProvider Services => host?.Services ?? throw new InvalidProgramException("host shouldn't be null");

    public static Window? Window => m_window;
}
