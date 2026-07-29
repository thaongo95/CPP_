import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import Qt.labs.platform 1.1

ApplicationWindow {
    id: window
    width: 1024
    height: 768
    visible: true
    title: "MBTiles Viewer"

    property string currentFile: ""
    property var metadata: ({})
    property int currentZoom: Math.floor(map.zoomLevel)
    property var currentCenter: QtPositioning.coordinate(
        Math.floor(map.center.latitude * 1000000) / 1000000,
        Math.floor(map.center.longitude * 1000000) / 1000000
    )

    function loadMBTiles(filePath) {
        if (mbtilesWrapper.openMBTiles(filePath)) {
            currentFile = filePath
            metadata = mbtilesWrapper.allMetadata()

            if (metadata["bounds"]) {
                var bounds = metadata["bounds"].split(',')
                if (bounds.length === 4) {
                    var sw = QtPositioning.coordinate(parseFloat(bounds[1]), parseFloat(bounds[0]))
                    var ne = QtPositioning.coordinate(parseFloat(bounds[3]), parseFloat(bounds[2]))
                    map.visibleRegion = QtPositioning.rectangle(sw, ne)
                }
            }

            if (metadata["center"]) {
                var center = metadata["center"].split(',')
                if (center.length === 3) {
                    map.center = QtPositioning.coordinate(parseFloat(center[1]), parseFloat(center[0]))
                    map.zoomLevel = parseFloat(center[2])
                }
            }

            fileInfo.text = "Loaded: " + currentFile + "\n" +
                         "Name: " + (metadata["name"] || "N/A") + "\n" +
                         "Format: " + (metadata["format"] || "N/A") + "\n" +
                         "Description: " + (metadata["description"] || "N/A") + "\n" +
                         "Version: " + (metadata["version"] || "N/A") + "\n" +
                         "Bounds: " + (metadata["bounds"] || "N/A")
        } else {
            fileInfo.text = "Failed to load: " + filePath
        }
    }

    FileDialog {
        id: fileDialog
        title: "Open MBTiles File"
        nameFilters: ["MBTiles files (*.mbtiles *.mbtile)", "All files (*)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            // Convert URL to local file path
            var filePath = Qt.resolvedUrl(fileDialog.file).toString().replace("file://", "");
            loadMBTiles(filePath);
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin {
            name: "osm" // Use OSM as base layer
        }
        center: QtPositioning.coordinate(21.34, 103.9) // London
        zoomLevel: 2

        gesture.enabled: true

        onZoomLevelChanged: {
            currentZoom = Math.floor(zoomLevel)
            currentCenter = QtPositioning.coordinate(
                Math.floor(center.latitude * 1000000) / 1000000,
                Math.floor(center.longitude * 1000000) / 1000000
            )
        }

        onCenterChanged: {
            currentCenter = QtPositioning.coordinate(
                Math.floor(center.latitude * 1000000) / 1000000,
                Math.floor(center.longitude * 1000000) / 1000000
            )
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            onWheel: {
                if (wheel.angleDelta.y > 0) {
                    map.zoomLevel = Math.min(map.zoomLevel + 1, 20)
                } else {
                    map.zoomLevel = Math.max(map.zoomLevel - 1, 0)
                }
            }
        }
    }

    // MBTiles overlay
    Image {
        id: tileImage
        anchors.fill: parent
        source: currentFile ? "image://mbtiles/" + currentZoom + "/" + currentCenter.longitude + "/" + currentCenter.latitude : ""
        fillMode: Image.PreserveAspectFit
        visible: currentFile
    }

    Rectangle {
        id: controlPanel
        width: parent.width
        height: fileInfo.implicitHeight + 60
        color: "#80000000"

        Column {
            anchors.fill: parent
            anchors.margins: 10

            Button {
                text: "Open MBTiles File"
                onClicked: fileDialog.open()
            }

            Text {
                id: fileInfo
                color: "white"
                width: parent.width
                wrapMode: Text.Wrap
                text: "No MBTiles file loaded"
            }
        }
    }

    Rectangle {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        width: 40
        height: 100
        color: "#80000000"
        radius: 5

        Column {
            anchors.centerIn: parent

            Button {
                text: "+"
                width: 30
                height: 30
                onClicked: map.zoomLevel = Math.min(map.zoomLevel + 1, 20)
            }

            Button {
                text: "-"
                width: 30
                height: 30
                onClicked: map.zoomLevel = Math.max(map.zoomLevel - 1, 0)
            }
        }
    }
}
