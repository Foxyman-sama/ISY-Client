import QtQuick
import QtQuick.Controls

Window {
    id: win
    width: 1920
    height: 1080
    visible: true
    title: "ISY"
    StackView {
        id: stack_view
        anchors.fill: parent
        initialItem: main_screen
        Keys.onBackPressed: pop();
    }
    MainScreen {
        id: main_screen
        onListButtonClicked: stack_view.push(list);
        onTouchButtonClicked: stack_view.push(touch_screen);
    }
    TouchScreen {
        id: touch_screen
        visible: false
    }
    List {
        id: list
        visible: false
        onSelectButtonClicked: {
            filecontrol.filename = list.filename_selected;
            stack_view.push(filecontrol);
        }
    }
    FileControl {
        id: filecontrol
        visible: false
        onFileDeleted: {
            stack_view.pop();
            client.receive();
        }
    }
}
