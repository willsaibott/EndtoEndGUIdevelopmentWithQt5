import QtQuick 2.12
import CM 1.0
import "../assets"

Item {
    property Client client

    implicitWidth: parent.width
    implicitHeight: Math.max(client_column.implicitHeight, text_address.implicitHeight) +
                    (Style.height_data_controls / 2)

    Rectangle {
        id:     background
        width:  parent.width
        height: parent.height
        color:  Style.colour_panel_background

        Column {
            id:     client_column
            width:  parent / 2
            anchors {
                left:       parent.left
                top:        parent.top
                margins:    Style.height_data_controls / 4
            }
            spacing: Style.height_data_controls / 2
            Text {
                id:             text_reference
                anchors.left:   parent.left
                text:           client.ui_reference.ui_label + ": " +
                                client.ui_reference.ui_value
                font.pixelSize: Style.pixel_size_data_controls
                color:          Style.colour_panel_font
            }
            Text {
                id: text_name
                anchors.left: parent.left
                text:         client.ui_name.ui_label + ": " +
                              client.ui_name.ui_value
                font.pixelSize: Style.pixel_size_data_controls
                color:          Style.colour_panel_font
            }
        }

        Text {
            id:  text_address
            anchors {
                top:     parent.top
                right:   parent.right
                margins: Style.height_data_controls / 4
            }
            text:  client.ui_supply_address.ui_full_address
            font.pixelSize: Style.pixel_size_data_controls
            color:          Style.colour_panel_font
            horizontalAlignment: Text.AlignRight
        }

        Rectangle {
            id: border_bottom
            anchors {
                bottom: parent.bottom
                left:   parent.left
                right:  parent.right
            }
            height: 1
            color:  Style.colour_panel_font
        }

        MouseArea {
            anchors.fill: parent
            cursorShape:  Qt.PointingHandCursor
            hoverEnabled: true
            onEntered:    background.state = "hover"
            onExited:     background.state = ""
            onClicked:    master_controller.select_client(client)
        }

        State {
            name: "hover"
            PropertyChanges {
                target: background
                color:  Style.colour_panel_background_hover
            }
        }
    }
}
