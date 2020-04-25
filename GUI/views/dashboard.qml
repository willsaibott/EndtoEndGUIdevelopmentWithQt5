import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    Rectangle {
        anchors {
            fill: parent
        }
        color:  "grey"
        Text {
            id:   dashboard_default_text
            text: qsTr("Dashboard")
            anchors.centerIn: parent
        }
        Button {
            text: "new..."
            onClicked: content_frame.replace("qrc:/views/new_client")
            anchors {
                bottom: parent.bottom
                right:  parent.right
                margins: 20
            }
        }
    }
}
