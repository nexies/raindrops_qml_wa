import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle
    {
        id: rotating_rect
        anchors.centerIn: parent
        height: 100
        width: 100
        color: "blue"
        Text
        {
            text: "HELLO!!!!"
            anchors.centerIn: parent
        }

        RotationAnimation on rotation {
            from: 0
            to: 360
            duration: 5000
            loops: Animation.Infinite
        }
    }



}
