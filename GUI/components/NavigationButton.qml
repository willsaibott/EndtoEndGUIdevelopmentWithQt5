import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import assets 1.0

Item {
    property alias icon_character: text_icon.text
    property alias description:    text_description.text
    property color hover_color:    Style.colour_navbar_on_hover

    signal navigationButtonClicked()

    width:  parent.width
    height: Style.height_navbtn

    Rectangle {
        id: background
        anchors {
            fill: parent
        }
        color: Style.colour_navbar_background
        Row {
          Text {
            width:  Style.width_navbtn_icon
            height: Style.height_navbtn_icon
            id:     text_icon
            font {
              family:    Style.fontAwesome
              pixelSize: 42
            }
            color:               Style.colour_navbar_foreground
            text:                "\uf11a"
            verticalAlignment:   Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
          }
          Text {
            id:                text_description
            width:             Style.width_navbtn_description
            height:            Style.height_navbtn_description
            color:             Style.colour_navbar_foreground
            text:              qsTr("")
            verticalAlignment: Text.AlignVCenter
            font.pixelSize:    Style.navbar_text_pixel_size
          }
        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target:  background
                    color:   hover_color
                }
            }
        ]

        MouseArea {
            anchors {
                fill: parent
            }
            cursorShape:  Qt.PointingHandCursor
            hoverEnabled: true
            onEntered:    background.state = "hover"
            onExited:     background.state = ""
            onClicked:    navigationButtonClicked()
        }
    }
}
