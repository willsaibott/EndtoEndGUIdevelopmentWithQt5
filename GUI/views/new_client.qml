import QtQuick 2.12
import components 1.0

Item {
    Rectangle {
        anchors {
            fill: parent
        }
        color:  "grey"
        Text {
            id:   create_client_default_text
            text: qsTr("Create Client View")
            anchors.centerIn: parent
        }
    }

    CommandBar {
        command_list: master_controller.ui_command_ctrl
                                       .ui_create_client_view_context_commands
    }
}
