import QtQuick 2.6
import QtQuick.Controls 1.2
import Qt.labs.settings 1.0
import "utilities.js" as Utils


ApplicationWindow{
    width: Utils.dp(400)
    height: Utils.dp(640)
    visible: true

    // default background color
    Rectangle {
        color: "#212126"
        anchors.fill: parent
    }

    // Toolbar
    toolBar: Rectangle{
        id: applicationBar
        y: 0
        width: parent.width
        height: Utils.dp(50)
        color: "#212126"
        opacity: 0.98
        Text{
            id: configText
            anchors.right: parent.right
            /* x: parent.width - 50 */
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            text: "Save"
            color: "white"
            font.pixelSize: Utils.dp(25)
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if (stackView.depth > 1){
                        configButtonClicked("config");
                        configText.text = "Save"
                    }
                    else{
                        configText.text = "Config"
                        configButtonClicked("save");
                    }
                }
            }
            /* Behavior on x{ */
            /*     NumberAnimation{ } */
            /* } */
        }
        /* states: [ */
        /*     State{ */
        /*         name: "xxx" */
        /*         PropertyChanges{ */
        /*             target: configText */
        /*             x: 100 */
        /*         } */
        /*     } */
        /* ] */
    }

    // Reset remote URL
    function configButtonClicked(mode){
        if (mode == "save"){
            /* applicationBar.state = "xxx" */
            var conf = stackView.currentItem;
            var host = conf.host;
            var username = conf.username;
            var password = conf.password;
            var port = conf.port;
            if (host.substr(0,4) != 'http'){
                host = 'http://' + host
            }
            if (parseInt(port) == 80){
                port = ''
            }
            else{
                port = ':' + port
            }
            var url = host + port + '/pi.jpg?u=' + username + '&p=' + password
            // update URL
            var qmlUrl = Qt.resolvedUrl("CamView.qml");
            stackView.push(qmlUrl);
            var camView = stackView.currentItem
            camView.url = url;
        }
        else{
            stackView.pop();
        }
    }

    // Stack view for switching between config window and cam view
    StackView{
        id: stackView
        anchors.fill: parent
        focus: true
        Keys.onReleased: {
            if (event.key === Qt.Key_Back && stackView.depth > 1) {
                configText.text = "Save"
                stackView.pop();
                event.accepted = true;
            }
        }
        initialItem: Qt.resolvedUrl("SettingsPage.qml");
    }
}
