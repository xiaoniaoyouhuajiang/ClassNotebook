import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.14

Item {
    Item {
        id: menu
        anchors.fill: parent
        Rectangle {
            anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter; leftMargin: 340; rightMargin:340}
            height: 400
            width: 600
            color: Qt.rgba(0.6, 0.6, 0.6, 0.6)
            radius: 30
            ColumnLayout {
                anchors.fill: parent
                spacing: 4
                MyButton {
                    Layout.alignment: Qt.AlignCenter
                    id: fullscreenToggleButton
                    _text: "Toggle Fullscreen"
                    Connections {
                        target: fullscreenToggleButton._mouseArea
                        function onClicked(mouse) {
                            if (window.visibility === Window.Windowed) {
                                window.showFullScreen()
                            }
                            else {
                                window.showNormal()
                            }
                        }
                    }
                }
                MyButton {
                    Layout.alignment: Qt.AlignCenter
                    id: quitButton
                    _text: "Back"
                    Connections {
                        target: quitButton._mouseArea
                        function onClicked(mouse) {
                            mainAppStackView.pop()
                        }
                    }
                }
            }
        }
    }

}
