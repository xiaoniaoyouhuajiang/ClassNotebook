import QtQuick 2.0
import QtQuick.Layouts 1.14
Item {
    property var _health: 0
    property var _armor: 0
    property var _attack: 0
    property var _name: ""
    Rectangle {
        anchors.fill: parent
        color: "white"
        border.color: "green"
        border.width: 2
        ColumnLayout {
            anchors.margins: 5
            anchors.fill: parent
            spacing: 2
            Text {
                id: name
                font.pointSize: 7
                text: "name: " + _name
            }
            Text {
                id: health
                font.pointSize: 7
                text: "health: " + _health
            }
            Text {
                id: armor
                font.pointSize: 7
                text: "armor: " + _armor
            }
            Text {
                id: attack
                font.pointSize: 7
                text: "attack: " + _attack
            }
        }
    }
}
