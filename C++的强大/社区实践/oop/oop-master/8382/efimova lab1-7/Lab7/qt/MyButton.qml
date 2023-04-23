import QtQuick 2.0

Text {
    property alias _text: buttonText.text
    property alias _color: buttonText.color
    property alias _mouseArea: buttonMouseArea
    id: buttonText
    color: "white"
    font.pointSize: 32
    font.bold: true
    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {parent.color = "orange"}
        onExited: {parent.color = "white"}
    }
}
