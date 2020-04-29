import QtQuick 2.12
import "../assets"

Item {
    property bool is_collapsed: true

    anchors {
        top:    parent.top
        bottom: parent.bottom
        left:   parent.left
    }
    width: is_collapsed ?
           Style.width_navbar_collapsed :
           Style.height_navbar_expanded

    Rectangle {
        clip:         true
        anchors.fill: parent
        color:        Style.colour_navbar_background

        Column {
            width: parent.width

            NavigationButton {
                icon_character:            "\uf0c9"
                description:               ""
                hover_color:               Style.colour_navbar_on_hover
                onNavigationButtonClicked: is_collapsed = !is_collapsed
            }
            NavigationButton {
                icon_character: "\uf015"
                description:    qsTr("Dashboard")
                hover_color:    Style.colour_navbar_on_hover
                onNavigationButtonClicked:
                    master_controller.ui_navigation_ctrl.showDashboardView()
            }
            NavigationButton {
                icon_character: "\uf234"
                description:    qsTr("New Client")
                hover_color:    Style.colour_navbar_on_hover
                onNavigationButtonClicked:
                    master_controller.ui_navigation_ctrl.showNewClientView()
            }
            NavigationButton {
                icon_character: "\uf002"
                description:    qsTr("Find Client")
                hover_color:    Style.colour_navbar_on_hover
                onNavigationButtonClicked:
                    master_controller.ui_navigation_ctrl.showSearchView()
            }
            NavigationButton {
                icon_character: "\uf09e"
                description:    qsTr("Rss Feed")
                hover_color:    Style.colour_navbar_on_hover
                onNavigationButtonClicked:
                    master_controller.ui_navigation_ctrl.showRssView()
            }
        }
    }
}
