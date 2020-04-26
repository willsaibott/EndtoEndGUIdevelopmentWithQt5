import QtQuick 2.12
import CM 1.0
import assets 1.0

Item {
    property Command command
    width:  Style.width_command_btn
    height: Style.height_command_btn

    Rectangle {
        id:           background
        anchors.fill: parent
        color:        Style.colour_command_bar_background

        Text {
            id:                  text_icon
            text:                command.ui_icon_character
            horizontalAlignment: Text.AlignHCenter
            color:               command.ui_can_execute ?
                                 Style.colour_command_bar_font :
                                 Style.colour_command_bar_font_disabled

            font {
                family:    Style.fontAwesome
                pixelSize: Style.pixel_size_command_bar_icon
            }

            anchors {
                centerIn:             parent
                verticalCenterOffset: -10
            }
        }

        Text {
            id: text_description
            anchors {
                top:    text_icon.bottom
                bottom: parent.bottom
                left:   parent.left
                right:  parent.right
            }
            font.pixelSize: Style.pixel_size_command_bar_text
            color:          command.ui_can_execute ?
                            Style.colour_command_bar_font :
                            Style.colour_command_bar_font_disabled
            text:           command.ui_description
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment:   Text.AlignVCenter
        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color:  Qt.darker(Style.colour_command_bar_background)
                }
            }
        ]

        MouseArea {
            anchors.fill: parent
            cursorShape:  Qt.PointingHandCursor
            hoverEnabled: true
            onEntered:    background.state = "hover"
            onExited:     background.state = ""
            onClicked: {
                if (command.ui_can_execute) {
                    command.executed();
                }
            }
        }

    }
}
