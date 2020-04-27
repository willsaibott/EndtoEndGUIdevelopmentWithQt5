import QtQuick 2.12
import QtQuick.Controls 2.12
import components 1.0
import CM 1.0
import assets 1.0

Item {
    property Client new_client: master_controller.ui_client


    Rectangle {
        anchors {
            fill: parent
        }
        color:  Style.colour_background
    }

    ScrollView {
        id: scrollview
        anchors {
            left:    parent.left
            right:   parent.right
            top:     parent.top
            bottom:  command_bar.top
            margins: Style.size_screen_margin
        }
        clip: true

        Column {
            spacing: Style.size_screen_margin
            width:   scrollview.width
            StringEditorSingleLine {
                string_decorator: new_client.ui_name
                anchors {
                    left:  parent.left
                    right: parent.right
                }
            }
        }
    }

    CommandBar {
        id: command_bar
        command_list: master_controller.ui_command_ctrl
                                       .ui_create_client_view_context_commands
    }
}
