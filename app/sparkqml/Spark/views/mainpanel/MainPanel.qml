import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0

FocusScope {
    id: item1
    implicitWidth: 640
    implicitHeight: 480

    property bool showErrorPanel: provider.errorString !== ""

    SplitView {
        anchors.fill: parent

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                spacing: 0
                anchors.fill: parent

                MainToolbar {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumHeight: 24

                }

                MainComponentViewer {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }

        StatesPanel {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumWidth: 240
        }

    }

    states: [
        State {
            name: "ShowErrorMessage"
            when: showErrorPanel

            PropertyChanges {
                target: errorPanel
                visible: true
                enabled: true
            }

            PropertyChanges {
                target: mask
                color: "#4c000000"
                opacity: 1
            }

            PropertyChanges {
                target: errorPlane
                opacity: 1
            }

            PropertyChanges {
                target: maskMouseArea
                enabled: true
                opacity: 1
            }
        }
    ]

    Item {
        id: errorPlane
        anchors.fill: parent
        opacity: 0

        MouseArea {
            id: maskMouseArea
            enabled: false
            anchors.fill: parent
            opacity: 0
            onClicked: {
                actions.closeErrorPanel();
            }

        }

        Rectangle {
            id: mask
            color: "#ffffff"
            anchors.fill: parent
            opacity: 0
        }

        ErrorPanel {
            id: errorPanel
            x: 70
            y: 90
            enabled: false
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

    }
}

