import QtQuick 2.12
import "../assets"
import "../components"
import CM 1.0

Item {
    property ClientSearch client_search: master_controller.ui_client_search

    Rectangle {
        anchors.fill: parent
        color: Style.colour_background

        Panel {
            id: search_panel
            anchors {
                left:    parent.left
                right:   parent.right
                top:     parent.top
                margins: Style.size_screen_margin
            }

            header_text: "Find Clients"
            content_component:
                StringEditorSingleLine {
                    string_decorator: client_search.ui_search_text
                    anchors {
                        left:   parent.left
                        right:  parent.right
                    }
                }
        }

        ListView {
            id: items_view
            anchors {
                top:     search_panel.bottom
                left:    parent.left
                right:   parent.right
                bottom:  parent.bottom
                margins: Style.size_screen_margin
            }
            clip:  true
            model: client_search.ui_search_results
            delegate:
                SearchResultDelegate {
                    client: modelData
                }
        }

        CommandBar {
            command_list:
                master_controller.ui_command_ctrl
                                 .ui_search_client_view_context_commands
        }
    }
}
