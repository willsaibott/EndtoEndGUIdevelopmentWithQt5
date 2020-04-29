import QtQuick 2.12
import CM 1.0
import assets 1.0

Panel {
    property Address address

    content_component:
        Column {
            id:      column
            spacing: Style.size_control_spacing
            StringEditorSingleLine {
                string_decorator: address.ui_building
                anchors {
                    left:   parent.left
                    right:  parent.right
                }
            }

            StringEditorSingleLine {
                string_decorator: address.ui_street
                anchors {
                    left:  parent.left
                    right: parent.right
                }
            }

            StringEditorSingleLine {
                string_decorator: address.ui_city
                anchors {
                    left:  parent.left
                    right: parent.right
                }
            }

            StringEditorSingleLine {
                string_decorator: address.ui_postcode
                anchors {
                    left:  parent.left
                    right: parent.right
                }
            }
        }
}
