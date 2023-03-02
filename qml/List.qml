import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ClientModel

Page {
    property string filename_selected: " "

    signal selectButtonClicked();
    Rectangle {
        id: rectangle
        anchors.bottom: refresh_button.top
        anchors.top: parent.top
        height: parent.height - refresh_button.height
        width: parent.width
        border.width: 2
        ListView {
            id: list_view
            anchors.centerIn: parent
            width: rectangle.width
            height: rectangle.height - 4
            clip: true
            model: ClientModel { }
            delegate: EventButton {
                id: delegate
                anchors.horizontalCenter: parent ? parent.horizontalCenter : undefined
                width: list_view.width - 20
                title: model.name
                onClicked: {
                    filename_selected = model.name;
                    selectButtonClicked();
                }
            }
        }
    }
    EventButton {
        id: refresh_button
        width: parent.width
        height: parent.height - rectangle.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        button_color: "white"
        button_border: 0
        title: "Обновить"
        onClicked: client.receive();
    }
}
