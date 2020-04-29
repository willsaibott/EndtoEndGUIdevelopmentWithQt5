import QtQuick 2.12
import "../assets"
import "../components"

Item {
    Rectangle {
        anchors {
            fill: parent
        }
        color: Style.colour_background
    }

    ListView {
        id:   items_view
        anchors {
            top:        parent.top
            left:       parent.left
            right:      parent.right
            bottom:     command_bar.top
            margins:    Style.size_header_margin
        }
        clip:   true
        model:  master_controller.ui_rss_channel ?
                master_controller.ui_rss_channel.ui_items :
                0
        delegate:   RssItemDelegate {
                        rss_item: modelData
                    }
    }


    CommandBar {
        id:    command_bar
        command_list: master_controller.ui_command_ctrl
                                       .ui_rss_view_context_commands
    }
}
