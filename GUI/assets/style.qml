pragma Singleton
import QtQuick 2.12

Item {
    property alias fontAwesome: font_awesome_loader.name

    readonly property color colour_background:         "#efefef"
    readonly property color colour_navbar_background:  "#000000"
    readonly property color colour_navbar_foreground:  "#A0A0FF"
    readonly property color colour_navbar_on_hover:    "#444444"
    readonly property int   pixel_size_navbar_icon:    42
    readonly property real  width_navbtn_icon:         80
    readonly property real  height_navbtn_icon:        width_navbtn_icon
    readonly property real  width_navbtn_description:  160
    readonly property real  height_navbtn_description: height_navbtn_icon
    readonly property real  width_navbtn:              width_navbtn_icon + width_navbtn_description
    readonly property real  height_navbtn:             Math.max(height_navbtn_icon, height_navbtn_description)
    readonly property real  width_navbar_collapsed:    width_navbtn_icon
    readonly property real  height_navbar_expanded:    width_navbtn
    readonly property int   navbar_text_pixel_size:    22


    readonly property real  width_command_btn:  80
    readonly property real  height_command_btn: width_command_btn

    readonly property color colour_command_bar_background:    "#cecece"
    readonly property color colour_command_bar_font:          "#131313"
    readonly property color colour_command_bar_font_disabled: "#636363"
    readonly property real  height_command_bar:               height_command_btn
    readonly property int   pixel_size_command_bar_icon:      32
    readonly property int   pixel_size_command_bar_text:      12

    readonly property real  size_screen_margin:              20
    readonly property color colour_data_controls_background: "#ffffff"
    readonly property color colour_data_controls_font:       "#131313"
    readonly property int   pixel_size_data_controls:        18
    readonly property real  width_data_controls:             400
    readonly property real  height_data_controls:            40

    FontLoader {
        id:     font_awesome_loader
        source: "qrc:/assets/fontawesome.otf"
    }
}

//readonly property color colour_navigation_bar_background: "#000000"
//readonly property color colour_navigation_bar_bar_font:   "#ffffff"
//readonly property int   pixel_size_navigation_bar_icon:   42


