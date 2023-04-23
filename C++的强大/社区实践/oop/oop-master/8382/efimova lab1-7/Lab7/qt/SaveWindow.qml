import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.14
import QtQuick.Dialogs 1.3

Item {
    anchors.fill: parent

    Rectangle {
        anchors.centerIn: parent
        width: 600
        height: 250
        color: Qt.rgba(0.6, 0.6, 0.6, 0.6)
        radius: 30
        TextField {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 50
            width: 500
            id: saveField
            color: "lightgray"
            font.pointSize: 15
            rightPadding: height
            clip: true
            readOnly: true
            text: saveDialog.fileUrl

            Image {
                fillMode: Image.PreserveAspectFit
                source: "../images/assets/folder_icon.png"
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 6
                Layout.alignment: Qt.AlignVCenter
                antialiasing: true
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        parent.source = "../images/assets/folder_icon_selected.png"
                    }
                    onExited: {
                        parent.source = "../images/assets/folder_icon.png"
                    }
                    onClicked: {
                        saveDialog.open()
                    }
                }
            }
            background: Rectangle {
                color: "gray"
                radius: 8
                implicitWidth: 500
            }
        }
        RowLayout {
            width: 500
            anchors.top: saveField.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            MyButton {
                text: "Save"
                Layout.alignment: Qt.AlignLeft
            }
            MyButton {
                text: "Back"
                Layout.alignment: Qt.AlignRight
            }
        }
    }
}
