import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.14
import game 1.0

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
                    id: newGameButton
                    _text: "New Game"
                    Connections {
                        target: newGameButton._mouseArea
                        function onClicked(mouse) {
                            mainAppStackView.push(newGameMenu)
                        }
                    }
                }
                MyButton {
                    Layout.alignment: Qt.AlignCenter
                    id: settingsButton
                    _text: "Settings"
                    Connections {
                        target: settingsButton._mouseArea
                        function onClicked(mouse) {
                            mainAppStackView.push(settingsMenu)
                        }
                    }
                }
                MyButton {
                    Layout.alignment: Qt.AlignCenter
                    id: quitButton
                    _text: "Quit"
                    Connections {
                        target: quitButton._mouseArea
                        function onClicked(mouse) {
							UIConnector.shutdown()
                            Qt.quit()
                        }
                    }
                }
            }
        }
    }
}
