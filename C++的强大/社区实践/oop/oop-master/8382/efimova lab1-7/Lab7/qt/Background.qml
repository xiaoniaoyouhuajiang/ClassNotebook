import QtQuick 2.0
import QtGraphicalEffects 1.12

Item {
    id: background
    anchors.fill: parent
    Image {
        id: background_img
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "images/main_menu_background.jpg"
    }
    GaussianBlur {
        anchors.fill: background_img
        source: background_img
        radius: 8
        samples: 16
    }
}
