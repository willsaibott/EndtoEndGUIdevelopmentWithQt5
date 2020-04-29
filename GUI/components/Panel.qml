import QtQuick 2.12
import "../assets"

Item {
    implicitWidth:  parent.width
    implicitHeight: header_background.height +
                    content_loader.implicitHeight + (Style.size_control_spacing * 2)

    property alias header_text:       title.text
    property alias content_component: content_loader.sourceComponent

    Rectangle {
        id:     shadow
        width:  parent.width
        height: parent.height
        x:      Style.size_shadow_offset
        y:      Style.size_shadow_offset
        color:  Style.colour_shadow
    }

    Rectangle {
        id: header_background
        anchors {
            top:   parent.top
            left:  parent.left
            right: parent.right
        }
        height: Style.height_panel_header
        color:  Style.colour_panel_header_background

        Text {
            id: title
            text: qsTr("null")
            anchors {
                fill:    parent
                margins: Style.height_data_controls / 4
            }
            color:              Style.colour_panel_header_font
            font.pixelSize:     Style.pixel_size_panel_header
            verticalAlignment:  Qt.AlignVCenter
        }
    }

    Rectangle {
        id: content_background
        anchors {
            top:    header_background.bottom
            left:   parent.left
            right:  parent.right
            bottom: parent.bottom
        }
        color: Style.colour_panel_background

        Loader {
            id:  content_loader
            anchors {
                left:    parent.left
                right:   parent.right
                top:     parent.top
                margins: Style.size_control_spacing
            }
        }
    }

}
