pragma Singleton
import QtQuick 2.12

Item {
    property alias fontAwesome: font_awesome_loader.name

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


    FontLoader {
        id:     font_awesome_loader
        source: "qrc:/assets/fontawesome.otf"
    }
}

//readonly property color colour_navigation_bar_background: "#000000"
//readonly property color colour_navigation_bar_bar_font:   "#ffffff"
//readonly property int   pixel_size_navigation_bar_icon:   42


