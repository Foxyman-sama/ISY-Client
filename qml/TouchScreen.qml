import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    MultiPointTouchArea {
        anchors.fill: parent
        touchPoints: [
            TouchPoint {
                id: point
            }
        ]
        onTouchUpdated: client.send(point.y.toString( ) + " " + point.x.toString(), "mouse");
    }
}
