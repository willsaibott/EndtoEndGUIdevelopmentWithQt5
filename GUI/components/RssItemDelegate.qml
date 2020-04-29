import QtQuick 2.12
import CM 1.0
import "../assets"

Item {
    property RssItem rss_item

    implicitWidth:  background.width
    implicitHeight: background.height

    Rectangle {
        id:     background
        width:  parent.width
        height: text_pub_date.implicitHeight + text_title.implicitHeight +
                border_bottom.height + (Style.size_item_margin * 3)
        color:  Style.colour_panel_background

        Text {
            id: text_pub_date
            anchors {
                top:     parent.top
                left:    parent.left
                right:   parent.right
                margins: Style.size_item_margin
            }
            text: Qt.formatDateTime(rss_item.ui_pub_date, "ddd, d MMM yyyy @ h:mm ap")
            font {
                pixelSize:  Style.pixel_size_data_controls
                italic:     true
                weight:     Font.Light
            }
            color: Style.colour_item_date_font
        }

        Text {
            id:     text_title
            anchors {
                top:        text_pub_date.bottom
                left:       parent.left
                right:      parent.right
                margins:    Style.size_item_margin
            }
            text:   rss_item.ui_title
            font {
                pixelSize: Style.pixel_size_data_controls
            }
            color:      Style.colour_item_title_font
            wrapMode:   Text.Wrap
        }

        Rectangle {
            id:     border_bottom
            anchors {
                top:        text_title.bottom
                left:       parent.left
                right:      parent.right
                topMargin:  Style.size_item_margin
            }
            height: 1
            color:  Style.colour_item_border
        }

        MouseArea {
            anchors.fill:   parent
            cursorShape:    Qt.PointingHandCursor
            hoverEnabled:   true
            onEntered:      background.state = "hover"
            onExited:       background.state = ""
            onClicked: {
                if (rss_item.ui_link !== "") {
                    Qt.openUrlExternally(rss_item.ui_link);
                }
            }
        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color:  Style.colour_panel_background_hover
                }
            }
        ]


    }
}
