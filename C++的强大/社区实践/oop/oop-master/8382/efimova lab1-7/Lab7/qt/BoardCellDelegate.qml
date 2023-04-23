import QtQuick 2.0
import QtQuick.Controls 2.0
import game 1.0

Component {
    Item {
        id: boardCellDelegate
        property bool isSelected: false
        property var statsRectangle: undefined
        property alias imagePath: unit_img.source

        function cellOnClicked() {
            if (board.state["invoking_cell"] === "empty" && _pongo_type !== "empty" && _user == board.currentUser) {
                board.state["invoking_cell"] = {"x": _x, "y": _y}
                isSelected = true
            }
            else if (board.state["invoking_cell"]["x"] === _x && board.state["invoking_cell"]["y"] === _y) {
                isSelected = false
                board.state = {"invoking_cell": "empty", "target_cell": "empty"}
            }

            else if (board.state.invoking_cell !== "empty"){
				var action = board.state
                action.target_cell = {"x": _x, "y": _y}
				var _action = board.checkAction(action)
				if(_action.actionType !== "empty") {
					board.state["target_cell"] = {"x": _x, "y": _y}
					board.sendAction()
				}
            }

            if(window._DEBUG_)
                console.log("Cell " + _x + "," + _y + " " + _terrain_type + " " + _pongo_type + " clicked")
        }

        function cellOnEntered() {
            if(_pongo_type !== "empty" && !isSelected) {
                var _width = 130
                var _height = 70
                var __x = _x * board.cell_size - (_width - board.cell_size/2)
                var __y = _y  * board.cell_size - _height
                var component = Qt.createComponent("UnitStats.qml")
                var object = component.createObject(boardFrame)
                object.x = __x
                object.y = __y
                object.width = _width
                object.height = _height
                if(_hasStats === 1) {
                    object._health = _health
                    object._armor = _armor
                    object._attack = _attack
                }
                object._name = _pongo_type
                statsRectangle = object
                background_content.border.color = "blue"
                background_content.border.width = 2
            }

            if(!isSelected && board.state.invoking_cell !== "empty") {
                var action = board.state
                action.target_cell = {"x": _x, "y": _y}
                var _action = board.checkAction(action)
                if(_action.actionType !== "empty")
                    background_content.border.color = "blue"
                else
                    background_content.border.color = "red"

                background_content.border.width = 2
            }
        }

        function cellOnExited() {
            if(statsRectangle) {
                statsRectangle.destroy()
            }

            if(!isSelected) {
                background_content.border.color = "gray"
                background_content.border.width = 0.5
            }
        }

        onIsSelectedChanged: {
            if(isSelected) {
                background_content.border.color = "orange"
                background_content.border.width = 2
            }
            else {
                background_content.border.color = "gray"
                background_content.border.width = 0.5
            }
        }

        Rectangle {
            id: cell
            height: board.cell_size
            width: board.cell_size
            color: "white"
            Image {
                id: terrain_img
                width: board.cell_size
                height: board.cell_size
                source: {
                    switch(_terrain_type) {
                    case "grass":
                        //"images/tiles/RPG_Nature_Tileset_grass_borderless_0" + (Math.floor(Math.random() * (4 - 1)) + 1) + ".png"
                        "images/tiles/grass_default.png"
                        break
                    case "snow":
                        "images/tiles/IceTileset_0" + (Math.floor(Math.random() * (4 - 1)) + 1) + ".png"
                        break
                    case "river":
                        "images/tiles/water_default.png"
                        break
                    default:
                        ""
                    }
                }
                smooth: false
            }

            Rectangle {
                id: background_content
                height: board.cell_size
                width: board.cell_size
                color: Qt.rgba(0,0,0,0)
                border.color: isSelected ? "orange" : "gray"
                border.width: 0.5
                anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}

            }

            Image {
                id: unit_img
                width: board.cell_size
                height: board.cell_size
                anchors.bottom: parent.bottom
                source: {
                    switch(_pongo_type) {
                    case "base":
                        "images/units/base_level_1.png"
                        break
                    case "stone":
                        "images/units/stone_01.png"
                        break
                    case "tree":
                        height = board.cell_size * 2
                        "images/units/tree_01.png"
                        break
                    case "tree_log":
                        "images/units/tree_log_01.png"
                        break
                    case "empty":
                        ""
                        break
                    default:
                        "images/units/light_cavalry_01.png"
                    }
                }
                smooth: false
            }
            Rectangle {
                id: debug_content
                height: board.cell_size
                width: board.cell_size
                color: Qt.rgba(0,0,0,0)
                anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
                Text {
                    id: _debug_coords
                    visible: {window._DEBUG_}
                    font.pointSize: 5
                    text: _x + " " + _y
                }
                Text {
                    id: _debug_terrain_type
                    visible: {window._DEBUG_}
                    anchors {right: parent.right; bottom: parent.bottom}
                    font.pointSize: 5
                    text: _terrain_type
                }
                Text {
                    id: _debug_unit_type
                    visible: {window._DEBUG_}
                    anchors {right: parent.right; top: parent.top}
                    font.pointSize: 5
                    text: _pongo_type
                }
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {cellOnEntered()}
                onExited: {cellOnExited()}
                onClicked: {cellOnClicked()}
            }
        }
    }
}
