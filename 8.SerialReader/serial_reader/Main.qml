import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

ApplicationWindow {
    visible: true
    width: 800
    height: 500
    title: "Z113 Serial Monitor"

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        //padding: 10
        RowLayout {
            spacing: 10
            ComboBox {
                id: portBox
                Layout.preferredWidth: 200
                model: serialManager.availablePorts
            }

            ComboBox {
                id: baudBox
                model: [9600, 19200, 38400, 57600, 115200]
                currentIndex: 0
            }
            Button {
                text: "Open"
                onClicked: {
                    if (portBox.currentIndex >= 0)
                        serialManager.openPort(
                            portBox.currentText,
                            baudBox.currentText
                        )
                }
            }
            Button {
                text: "Close"
                onClicked: serialManager.closePort()
            }
            Button {
                text: "Clear"
                onClicked: content.text = ""
            }
        }
        Rectangle{
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#805f9ea0"
            TextArea {
                id: content
                Layout.fillWidth: true
                Layout.fillHeight: true
                readOnly: true
                wrapMode: TextArea.Wrap
                text: serialManager.receivedText
            }
        }
    }
    Rectangle{
        id: bg
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width/2
        height: parent.height/3
        color: "lightblue"
        radius: width/3
        Repeater {
            model: 61   // 0 → 120 step 10
            Rectangle {
                width: 2
                height: (index%5===0) ? ((index%10===0) ? 15 : 10) : 5
                color: "white"

                anchors.top: bg.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 30 //(index%5===0) ? ((index%10===0) ? 5 : 10) : 15
                Text{
                    anchors.bottom: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: (index%5===0) ? index : ""
                    color: "white"

                }
                transform: Rotation {
                    origin.x: 0
                    origin.y: bg.height/3*2
                    angle: -90 + index * 3
                }
            }
        }
        Rectangle{
            id: needle
            anchors.right: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height/3-30
            width: parent.height*2/3 -30
            height: 2
            transform: Rotation {
                origin.x: needle.width
                origin.y: needle.height/2
                angle: serialManager.value*3.0
            }
            color: "red"
        }
    }
    Rectangle{
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
        width: 30
        height: 180
        border.color: "black"
        border.width: 2
        color: "lightgray"
        Rectangle{
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: serialManager.value*3
            color: "green"
        }
    }
}
