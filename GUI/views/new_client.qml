import QtQuick 2.12
import QtQuick.Controls 2.12
import CM 1.0
import "../components"
import "../assets"

Item {
    property Client new_client: master_controller.ui_client

    ScrollView {
        id:  scrollview
        anchors {
            left:    parent.left
            right:   parent.right
            top:     parent.top
            bottom:  command_bar.top
            margins: Style.size_screen_margin
        }
        clip: true

        Column {
            width: scrollview.width
            spacing: Style.size_control_spacing

            Panel {
                header_text: qsTr("Client Details")
                content_component:
                    Column {
                        spacing: Style.size_control_spacing

                        StringEditorSingleLine {
                            string_decorator: new_client.ui_reference
                            anchors {
                                left:  parent.left
                                right: parent.right
                            }
                        }

                        StringEditorSingleLine {
                            string_decorator: new_client.ui_name
                            anchors {
                                left:  parent.left
                                right: parent.right
                            }
                        }
                    }
            }

            AddressEditor {
                address:     new_client.ui_supply_address
                header_text: qsTr("Supply Address")
            }

            AddressEditor {
                address:    new_client.ui_billing_address
                header_text: qsTr("Billing Address")
            }
        }

    }

    CommandBar {
        id: command_bar
        command_list: master_controller.ui_command_ctrl
                                       .ui_create_client_view_context_commands
    }
}
