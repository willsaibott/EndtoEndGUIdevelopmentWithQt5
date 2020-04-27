import QtQuick 2.12
import assets 1.0

Item {
    Rectangle {
        anchors {
            fill: parent
        }
        color:  Style.colour_background
        Text {
            id:   splash_welcome_text
            text: qsTr("Welcome to Client Manager")
            anchors.centerIn: parent
        }
    }
}
