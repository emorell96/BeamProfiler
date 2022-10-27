import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls.Universal 2.12

import Qt.labs.platform as Platform
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Dialogs
import QtQuick.Layouts

ApplicationWindow {
    Universal.theme: Universal.Dark
    Universal.accent: Universal.Violet

    visible: true
    width: 640
    height: 480
    title: qsTr("Beam Profiler")

    StackLayout
    {
        GroupBox {
        title: qsTr("Initial Parameters")
        StackLayout {
            Label{
                text: "x_0"
                }
            SpinBox {
                value: 50
                from: 0
                to: 10000
                }
            }
        }
        MenuBar {
            Universal.theme: Universal.Dark
            Universal.accent: Universal.Violet
            Menu {
                Universal.theme: Universal.Dark
                Universal.accent: Universal.Violet
                title: qsTr("&File")

                MenuItem {
                    Universal.theme: Universal.Dark
                    Universal.accent: Universal.Violet
                    text: qsTr("&Open")
                    onTriggered: openDialog.open()
                }
            
                MenuItem {
                    text: qsTr("&Quit")
                    onTriggered: close()
                }
            }
        }

      
    }
    

    FileDialog {
        id: openDialog
        fileMode: FileDialog.OpenFile
        selectedNameFilter.index: 1
        nameFilters: ["Images (*.bmp *.png *.jpg *.jpeg)"]
        currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: document.load(selectedFile)
    }
}
