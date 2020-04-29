import QtQuick 2.12
import assets 1.0

Item {
    property alias command_list: command_repeater.model

    anchors {
        left:   parent.left
        bottom: parent.bottom
        right:  parent.right
    }

    height: Style.height_command_bar

    Rectangle {
        anchors.fill: parent
        color:        Style.colour_command_bar_background

        Row {
            anchors {
                top:    parent.top
                bottom: parent.bottom
                right:  parent.right
            }

            Repeater {
                id:       command_repeater
                delegate: CommandButton {
                    command: modelData
                }
            }
        }
    }

}
