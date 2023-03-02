import QtQuick
import QtQuick.Controls

Button {
    property alias button_radius: background_rect.radius
    property alias button_border: background_rect.border.width
    property alias button_color: background_rect.color
    property string title: ""

    id: root
    width: 200
    height: 50
    background: Rectangle {
        id: background_rect
        radius: 8
        border.width: 2
        color: "white"
    }
    Text {
        id: text
        anchors.centerIn: parent
        text: title
    }
}
