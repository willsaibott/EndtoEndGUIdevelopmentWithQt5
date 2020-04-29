import QtQuick 2.12
import CM 1.0
import "../assets"

Item {
    property StringDecorator string_decorator

    height: width > text_label.width + text_value.width ?
            Style.height_data_controls :
            Style.height_data_controls * 2

    Flow {
        anchors.fill: parent

        Rectangle {
            width:        Style.width_data_controls
            height:       Style.height_data_controls
            color:        Style.colour_panel_background

            Text {
                id: text_label
                anchors {
                    fill:    parent
                    margins: Style.height_data_controls / 4
                }
                text:              string_decorator.ui_label
                color:             Style.colour_data_controls_font
                font.pixelSize:    Style.pixel_size_data_controls
                verticalAlignment: Qt.AlignVCenter
            }
        }

        Rectangle {
            id: background
            width:   Style.width_data_controls
            height:  Style.height_data_controls
            color:   Style.colour_data_controls_background
            border {
                width: 1
                color: Style.colour_data_controls_font
            }
            TextInput {
                id: text_value
                anchors {
                    fill: parent
                    margins: Style.height_data_controls / 4
                }
                text:               string_decorator.ui_value
                color:              Style.colour_data_controls_font
                font.pixelSize:     Style.pixel_size_data_controls
                verticalAlignment:  Qt.AlignVCenter
            }
        }

        Binding {
            target:     string_decorator
            property:   "ui_value"
            value:      text_value.text
        }
    }
}
