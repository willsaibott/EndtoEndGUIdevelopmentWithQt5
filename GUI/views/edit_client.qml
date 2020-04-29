import QtQuick 2.12
import QtQuick.Controls 2.12
import CM 1.0
import "../assets"
import "../components"


Item {
    property Client client
    property Client local_temp_client
    property Client client_to_bind: client ? client : local_temp_client
    Component.onCompleted: master_controller.ui_command_ctrl.set_selected_client(client)

    Rectangle {
        anchors.fill: parent
        color:        Style.colour_background
    }

    ScrollView {
        id: scrollview
        anchors {
            left:       parent.left
            right:      parent.right
            top:        parent.top
            bottom:     command_bar.top
            margins:    Style.size_screen_margin
        }
        clip: true
        Column {
            spacing: Style.size_screen_margin
            width:   scrollview.width

            Panel {
                header_text: "Client details"
                content_component:
                    Column {
                        spacing: Style.size_control_spacing
                        StringEditorSingleLine {
                            string_decorator: client_to_bind.ui_reference
                            anchors {
                                left:   parent.left
                                right:  parent.right
                            }
                        }
                        StringEditorSingleLine {
                            string_decorator: client_to_bind.ui_name
                            anchors {
                                left:   parent.left
                                right:  parent.right
                            }
                        }
                    }
            }

            AddressEditor {
                address:        client_to_bind.ui_supply_address
                header_text:    "Supply Address"
            }

            AddressEditor {
                address:        client_to_bind.ui_billing_address
                header_text:    "Billing Address"
            }
        }
    }

    CommandBar {
        id:   command_bar
        command_list: master_controller.ui_command_ctrl
                                       .ui_edit_client_view_context_commands

    }
}
