import QtQuick 2.6
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import Qt.labs.settings 1.0
import "utilities.js" as Utils


Item{
    width: parent.width
    height: parent.width

    Settings {
        property alias host: hostField.text
        property alias port: portField.text
        property alias username: usernameField.text
        property alias password: passwordField.text
    }

    property string host: hostField.text
    property string port: portField.text
    property string username: usernameField.text
    property string password: passwordField.text

    Column{
        spacing: Utils.dp(40)
        anchors.centerIn: parent

        TextField{
            id: hostField
            anchors.margins: 20
            placeholderText: "host"
            style: touchStyle
        }
        TextField{
            id: portField
            anchors.margins: 20
            text: "80"
            validator: IntValidator {bottom: 80; top: 9000;}
            style: touchStyle
        }
        TextField{
            id: usernameField
            anchors.margins: 20
            placeholderText: "username"
            style: touchStyle
        }
        TextField{
            id: passwordField
            anchors.margins: 20
            echoMode: TextInput.PasswordEchoOnEdit
            placeholderText: "password"
            style: touchStyle
        }
    }

    Component {
        id: touchStyle
        TextFieldStyle {
            textColor: "white"
            placeholderTextColor: "#6c6c6c"
            font.pixelSize: Utils.dp(28)
            background: Item {
                implicitHeight: Utils.dp(50)
                implicitWidth: Utils.dp(320)
                BorderImage {
                    source: "img/textinput.png"
                    border.left: 8
                    border.right: 8
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
            }
        }
    }

}

