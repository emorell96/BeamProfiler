// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using BeamProfilerSharp.Pages;
using Microsoft.UI;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Media.Animation;
using Microsoft.UI.Xaml.Navigation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.ApplicationSettings;
using WinRT.Interop;


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace BeamProfilerSharp;
/// <summary>
/// An empty window that can be used on its own or navigated to within a Frame.
/// </summary>
public sealed partial class MainWindow : Window
{
    private AppWindow? m_AppWindow;
    public MainWindow()
    {
        this.InitializeComponent();
        SetTitleBarColors();
        //m_AppWindow = GetAppWindowForCurrentWindow();
        Title = "Beam Profiler";
        NavigationViewControl.IsSettingsVisible = false;
    }

    private AppWindow GetAppWindowForCurrentWindow()
    {
        IntPtr hWnd = WindowNative.GetWindowHandle(this);
        WindowId wndId = Win32Interop.GetWindowIdFromWindow(hWnd);
        return AppWindow.GetFromWindowId(wndId);
    }

    private void NavView_ItemInvoked(NavigationView sender,
                                 NavigationViewItemInvokedEventArgs args)
    {
        if (args.IsSettingsInvoked == true)
        {
            NavView_Navigate("settings", args.RecommendedNavigationTransitionInfo);
        }
        else if (args.InvokedItemContainer != null)
        {
            var navItemTag = args.InvokedItemContainer.Tag.ToString();
            NavView_Navigate(navItemTag, args.RecommendedNavigationTransitionInfo);
        }
    }

    private void NavView_Navigate(
    string? navItemTag,
    NavigationTransitionInfo transitionInfo)
    {
        Type? _page = null;
        if (navItemTag == "home")
        {
            _page = typeof(AnalysisPage);
        }

        // Get the page type before navigation so you can prevent duplicate
        // entries in the backstack.
        var preNavPageType = ContentFrame.CurrentSourcePageType;

        // Only navigate if the selected page isn't currently loaded.
        if (_page is not null && !Type.Equals(preNavPageType, _page))
        {
            ContentFrame.Navigate(_page, null, transitionInfo);
        }
    }

    private bool SetTitleBarColors()
    {
        // Check to see if customization is supported.
        // Currently only supported on Windows 11.
        if (AppWindowTitleBar.IsCustomizationSupported())
        {
            if (m_AppWindow is null)
            {
                m_AppWindow = GetAppWindowForCurrentWindow();
            }
            var titleBar = m_AppWindow.TitleBar;

            // Set active window colors
            //titleBar.ForegroundColor = Colors.White;
            titleBar.BackgroundColor = Colors.Black;
            //titleBar.ForegroundColor = Colors.DarkGray;

            //// Set inactive window colors
            //titleBar.InactiveForegroundColor = Colors.Gainsboro;
            //titleBar.InactiveBackgroundColor = Colors.SeaGreen;
            //titleBar.ButtonInactiveForegroundColor = Colors.Gainsboro;
            //titleBar.ButtonInactiveBackgroundColor = Colors.SeaGreen;
            return true;
        }
        return false;
    }

    private void ContentFrame_Navigated(object sender, NavigationEventArgs e)
    {
        NavigationViewControl.IsBackEnabled = ContentFrame.CanGoBack;

        //if (ContentFrame.SourcePageType == typeof(AnalysisPage))
        //{
        //    // SettingsItem is not part of NavView.MenuItems, and doesn't have a Tag.
        //    NavigationViewControl.SelectedItem = (NavigationViewItem)NavigationViewControl.SettingsItem;
        //    NavView.Header = "Settings";
        //}
        if (ContentFrame.SourcePageType != null)
        {
            var item = typeof(AnalysisPage);

            NavigationViewControl.SelectedItem = NavigationViewControl.MenuItems
                .OfType<NavigationViewItem>()
                .First(n => n.Tag.Equals("home"));

            //NavigationViewControl.Header =
            //    ((NavigationViewItem)NavigationViewControl.SelectedItem)?.Content?.ToString();
        }
        
    }

    private void NavigationViewControl_Loaded(object sender, RoutedEventArgs e)
    {
        NavigationViewControl.SelectedItem = NavigationViewControl.MenuItems[0];
        NavView_Navigate("home", new EntranceNavigationTransitionInfo());
    }
}
