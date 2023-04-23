import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.14
import QtQuick.Shapes 1.12

Item {
    anchors.fill: parent
    property alias _boardHeight: boardHeight.text
    property alias _boardWidth: boardWidth.text
    Rectangle {
        anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter; leftMargin: 340; rightMargin:340}
        height: 600
        width: 1000
        color: Qt.rgba(0.6, 0.6, 0.6, 0.6)
        radius: 30
        RowLayout {
            id: settingsLayout
            anchors.fill: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.topMargin: 50
            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                spacing: 100
                RowLayout {
                    Layout.alignment: Qt.AlignLeft
                    Text {
                        id: boardHeightSetting
                        font.pointSize: 32
                        font.bold: true
                        text: "Board height: "
                        color: "white"
                    }
                    Item {
                        width: boardHeight.width
                        height: boardHeight.height
                        TextField {
                            id: boardHeight
                            width:84
                            background: Rectangle {
                                color: "gray"
                                border.width: 3
                                border.color: Qt.rgba(0, 0, 0, 0)
                            }
                            onFocusChanged: {
                                if(focus)
                                    background.border.color = "orange"
                                else
                                    background.border.color = Qt.rgba(0, 0, 0, 0)
                            }
                            font.pointSize: 32
                            font.bold: true
                            text: "50"
                            color: "white"
                            onTextChanged: {
                                if(text >= 100)
                                    text = "99"
                            }
                        }
                        Image {
                            width: 50
                            height: 50
                            source: "images/assets/triangle_button.png"
                            anchors.bottom: parent.top
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottomMargin: 5
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onEntered: {
                                    parent.source = "images/assets/triangle_button_selected.png"
                                }
                                onExited: {
                                    parent.source = "images/assets/triangle_button.png"
                                }
                                onClicked: {
                                    boardHeight.text++
                                }
                            }
                        }
                        Image {
                            width: 50
                            height: 50
                            source: "images/assets/triangle_button.png"
                            transformOrigin: Item.Center
                            rotation: 180
                            anchors.top: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.topMargin: 5
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onEntered: {
                                    parent.source = "images/assets/triangle_button_selected.png"
                                }
                                onExited: {
                                    parent.source = "images/assets/triangle_button.png"
                                }
                                onClicked: {
                                    boardHeight.text--
                                }
                            }
                        }
                    }
                }
                MyButton {
                    Layout.alignment: Qt.AlignCenter
                    id: startGameButton
                    _text: "Start Game"
                    Connections {
                        target: startGameButton._mouseArea
                        function onClicked(mouse) {
                            mainAppStackView.push(board_d)
                        }
                    }
                }
            }
            ColumnLayout {
                spacing: 100
                Layout.alignment: Qt.AlignTop
                RowLayout {
                Layout.alignment: Qt.AlignRight
                    Text {
                        id: boardWidthSetting
                        font.pointSize: 32
                        font.bold: true
                        text: "Board width: "
                        color: "white"
                    }
                    Item {
                        height: boardWidth.height
                        width: boardWidth.width
                        TextField {
                            id: boardWidth
                            background: Rectangle {
                                color: Qt.rgba(0.6, 0.6, 0.6, 0.6)
                                border.width: 3
                                border.color: Qt.rgba(0, 0, 0, 0)
                            }
                            onFocusChanged: {
                                if(focus)
                                    background.border.color = "orange"
                                else
                                    background.border.color = Qt.rgba(0, 0, 0, 0)
                            }

                            font.pointSize: 32
                            font.bold: true
                            text: "50"
                            color: "white"
                            onTextChanged: {
                                if(text < 0)
                                    text = "0"
                            }
                        }
                        Image {
                            width: 50
                            height: 50
                            source: "images/assets/triangle_button.png"
                            anchors.bottom: parent.top
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottomMargin: 5
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onEntered: {
                                    parent.source = "images/assets/triangle_button_selected.png"
                                }
                                onExited: {
                                    parent.source = "images/assets/triangle_button.png"
                                }
                                onClicked: {
                                    boardWidth.text++
                                }
                            }
                        }
                        Image {
                            width: 50
                            height: 50
                            source: "images/assets/triangle_button.png"
                            transformOrigin: Item.Center
                            rotation: 180
                            anchors.top: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.topMargin: 5
                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onEntered: {
                                    parent.source = "images/assets/triangle_button_selected.png"
                                }
                                onExited: {
                                    parent.source = "images/assets/triangle_button.png"
                                }
                                onClicked: {
                                    boardWidth.text--
                                }
                            }
                        }
                    }
                }
                MyButton {
                    Layout.alignment: Qt.AlignCenter
                    id: backButton
                    _text: "Back"
                    Connections {
                        target: backButton._mouseArea
                        function onClicked(mouse) {
                            mainAppStackView.pop()
                        }
                    }
                }
            }
        }
    }
}
