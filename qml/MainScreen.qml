import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

Page {
    signal listButtonClicked();
    signal touchButtonClicked();

    id: root
    MessageDialog {
        id: info_dialog
        text: "Первая строка для ip - адреса.\ndddd
               Вторая строка - для порта\клавиатурного ввода\частотного звука.\n
               Клавиатурный ввод вида: AFSDIHFE!, где ! - Enter.\n
               Частотный ввод вида: 100 10, где 100 частота, а 10 - длительность."
        onButtonClicked: close();
    }
    FileDialog {
        id: file_dialog
        onAccepted: client.send(selectedFile, "file");
    }
    Text {
        id: connect_text
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: top_field.top
        color: "springgreen"
        visible: client.is_connected ? true : false
        text: "Соединение с " + top_field.text
    }
    TextField {
        id: top_field
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: bottom_field.top
        anchors.bottomMargin: 10
        horizontalAlignment: TextInput.Center
        height: 40
        width: connect_button.width
        text: "192.168.0.111"
        visible: client.is_connected ? false : true
    }
    TextField {
        id: bottom_field
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: connect_button.top
        anchors.bottomMargin: 40    
        horizontalAlignment: TextInput.Center
        height: 40
        width: connect_button.width
        text: client.is_connected ? "" : "9090"
    }
    EventButton {
        id: connect_button
        anchors.centerIn: parent
        title: client.is_connected ? "Разорвать соединение" : "Установить соединение"
        onClicked: client.is_connected
                   ? client.disconnect()
                   : client.connect(top_field.text, bottom_field.text);
    }
    EventButton {
        id: info_button
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        width: 40
        height: 40
        title: "i"
        onClicked: info_dialog.open();
    }
    EventButton {
        id: console_button
        anchors.top: connect_button.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        title: "Консольная команда"
        visible: client.is_connected ? true : false
        onClicked: client.send(bottom_field.text, "cmd");
    }
    EventButton {
        id: input_button
        anchors.top: console_button.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        title: "Ввод"
        visible: client.is_connected ? true : false
        onClicked: client.send(bottom_field.text, "input");
    }
    EventButton {
        id: mouse_button
        anchors.top: input_button.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        title: "Позиция курсора"
        visible: client.is_connected ? true : false
        onClicked: touchButtonClicked();
    }
    EventButton {
        id: send_button
        anchors.top: mouse_button.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        title: "Отправить файл"
        visible: client.is_connected ? true : false
        onClicked: file_dialog.open();
    }
    EventButton {
        id: list_button
        anchors.top: send_button.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        title: "Лист доступных файлов"
        visible: client.is_connected ? true : false
        onClicked: listButtonClicked();
    }   
    EventButton {
        id: beep_button
        anchors.top: list_button.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        title: "Частотный звук"
        visible: client.is_connected ? true : false
        onClicked: client.send(bottom_field.text, "beep");
    }
}
