import QtQuick 2.0
import game 1.0
import QtQuick.Dialogs 1.3

Item {
    Loader {
        id: boardLoader
        asynchronous: true
        anchors.fill: parent
        onLoaded: {
            item.populateBoard(newGameMenu._boardWidth, newGameMenu._boardHeight)
            loadingText.visible = false
        }
    }

    function changeVisibility(mode) {
        if(mode)
            loadingText.visible = true
        else
            loadingText.visible = false
    }

    Text {
        id: backButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 20
        text: "Back"
        font.pointSize: 32
        font.bold: true
        color: "white"
        style: Text.Outline
        styleColor: "orange"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {parent.color = "orange"}
            onExited: {parent.color = "white"}
            onClicked: {
                boardLoader.source = ""
                mainAppStackView.pop()
            }
        }
    }
    Text {
        id: initButton
        anchors.top: backButton.bottom
        anchors.right: parent.right
        anchors.leftMargin: 20
        text: "Init"
        font.pointSize: 32
        font.bold: true
        color: "white"
        style: Text.Outline
        styleColor: "orange"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {parent.color = "orange"}
            onExited: {parent.color = "white"}
            onClicked: {
                loadingText.visible = true
                boardLoader.item.populateBoard(newGameMenu._boardWidth, newGameMenu._boardHeight)
                loadingText.visible = false
            }
        }
    }
    Text {
        id: debugSwitchButton
        anchors.top: initButton.bottom
        anchors.right: parent.right
        anchors.leftMargin: 20
        text: "Debug"
        font.pointSize: 32
        font.bold: true
        color: "white"
        style: Text.Outline
        styleColor: "orange"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {parent.color = "orange"}
            onExited: {parent.color = "white"}
            onClicked: {
                if(window._DEBUG_ === false)
                    window._DEBUG_ = true
                else
                    window._DEBUG_ = false
            }
        }
    }

    Text {
        id: saveButton
        anchors.top: debugSwitchButton.bottom
        anchors.right: parent.right
        anchors.leftMargin: 20
        text: "Save"
        font.pointSize: 32
        font.bold: true
        color: "white"
        style: Text.Outline
        styleColor: "orange"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {parent.color = "orange"}
            onExited: {parent.color = "white"}
            onClicked: {
                saveDialog.open()
            }
        }
    }

    Text {
        id: loadButton
        anchors.top: saveButton.bottom
        anchors.right: parent.right
        anchors.leftMargin: 20
        text: "Load"
        font.pointSize: 32
        font.bold: true
        color: "white"
        style: Text.Outline
        styleColor: "orange"
        FileDialog {
            id: saveDialog
            defaultSuffix: ".save"
            selectMultiple: false
            selectFolder: false
            selectExisting: false
            nameFilters: [ "BoardGame save file (*.save)"]
            height: 400
            width: 500
            onAccepted: {
                    console.log(fileUrl)
                    UIConnector.save(fileUrl)
                }
        }
        FileDialog {
            id: loadDialog
            defaultSuffix: ".save"
            selectMultiple: false
            selectFolder: false
            nameFilters: [ "BoardGame save file (*.save)"]
            height: 400
            width: 500
            onAccepted: {
                    changeVisibility(true)
                    var prop = UIConnector.load(fileUrl)
                    boardLoader.item.loadBoard(prop.sizeX, prop.sizeY)
                    changeVisibility(false)
                }
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {parent.color = "orange"}
            onExited: {parent.color = "white"}
            onClicked: {
                loadDialog.open()
            }
        }
    }
    onVisibleChanged: {
        if(visible) {
            console.log("wtf2")
            boardLoader.source = "Board.qml"
        }
    }
    Text {
        id: loadingText
        anchors.centerIn: parent
        font.pointSize: 35
        text: "Loading"
        color: "white"
        font.bold: true
        visible: true
    }
}
