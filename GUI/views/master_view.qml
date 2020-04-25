import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import assets 1.0
import components 1.0

Window {
    id:      master_window
    visible: true
    width:   640
    height:  480
    title:   qsTr("Client Management")

    Connections {
        target:              master_controller.ui_navigation_ctrl
        onShowNewClientView: content_frame.replace("qrc:/views/new_client")
        onShowDashboardView: content_frame.replace("qrc:/views/dashboard")
        onShowEditView:      content_frame.replace("qrc:/views/edit_client", { selected_client: client })
        onShowSearchView:    content_frame.replace("qrc:/views/search_client")
    }

    StackView {
        id:           content_frame
        initialItem:  Qt.resolvedUrl("qrc:/views/splash_view")
        anchors {
            fill: parent
        }
        Timer {
            interval: 2000
            running:  true
            repeat:   false
            onTriggered: {
                console.log(Date().toString())
                content_frame.replace("qrc:/views/dashboard")
                content_frame.anchors.top    = master_window.top;
                content_frame.anchors.bottom = master_window.bottom;
                content_frame.anchors.right  = master_window.right;
                content_frame.anchors.left   = navigation_bar.right;
                navigation_bar.visible       = true
            }
        }
//        Component.onCompleted: {
//            content_frame.replace("qrc:/views/dashboard")
//        }
    }

    NavigationBar {
        id:      navigation_bar
        visible: false
    }
}
