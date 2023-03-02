import QtQuick
import QtQuick.Controls

Page {
    property string filename: " "

    signal backButtonClicked();
    signal fileDeleted();
    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: start_button.top
        text: filename
    }
    EventButton {
        id: start_button
        title: "Запустить"
        anchors.centerIn: parent
        onClicked: client.send("start files\\" + filename, "cmd");
    }
    EventButton {
        id: delete_button
        title: "Удалить"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: start_button.bottom
        onClicked: {
            client.send("del /f files\\" + filename, "cmd");
            fileDeleted();
        }
    }
    EventButton {
        id: wallpaper_button
        title: "Установить на обои"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: delete_button.bottom
        visible: filename.match(".png") ? true : false
        onClicked: client.send(filename, "wallpaper");
    }
}
