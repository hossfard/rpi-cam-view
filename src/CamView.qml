import Rpi 1.0
import QtQuick 2.6
import QtQuick.Controls 1.2


Item{
    property alias url: image.url
    Flickable{
        id: flick
        contentWidth: parent.width
        contentHeight: parent.height

        Rectangle{
            id: container
            x: 0
            height: parent.height
            width: parent.width
            color: "#212126"
            // Setting anchors.fill will make it non-draggable
            // anchors.fill: parent

            RemoteImage{
                id: image
                anchors.fill: parent
                /* url: "https://pi.zshbox.com/pi.jpg?u=YWRtaW4=&p=TFNLKigzaG5C" */
                /* url: "http://192.168.1.72:8080/pi.jpg?u=YWRtaW4=&p=TFNLKigzaG5C" */
            }

            PinchArea{
                anchors.fill: parent
                pinch.target: container
                pinch.minimumRotation: -360
                pinch.maximumRotation: 360
                pinch.minimumScale: .5
                pinch.maximumScale: 10
                pinch.minimumX: -100
                pinch.maximumX: 100
                pinch.dragAxis: Pinch.XAndYAxis

                // This *needs* to be a child of PinchArea, otherwise,
                // it will eat up press evens
                MouseArea{
                    id: dragArea
                    anchors.fill: parent
                    drag.target: container
                    // pass 2-finger-flick gesture to the Flickable
                    scrollGestureEnabled: false
                    onWheel: {
                        container.scale += container.scale * wheel.angleDelta.y / 120 / 10;
                    }
                }

                /* onSmartZoom: { */
                /*     if (pinch.scale > 0) { */
                /*         /\* container.rotation = 0; *\/ */
                /*         container.scale = Math.min(root.width, root.height) / Math.max(image.sourceSize.width, image.sourceSize.height) * 0.85 */
                /*         container.x = flick.contentX + (flick.width - container.width) / 2 */
                /*         container.y = flick.contentY + (flick.height - container.height) / 2 */
                /*     } else { */
                /*         container.rotation = pinch.previousAngle */
                /*         container.scale = pinch.previousScale */
                /*         container.x = pinch.previousCenter.x - container.width / 2 */
                /*         container.y = pinch.previousCenter.y - container.height / 2 */
                /*     } */
                /* } */
            }

            /* MouseArea{ */
            /*     id: dragArea */
            /*     anchors.fill: parent */
            /*     drag.target: image */
            /*     scrollGestureEnabled: false */
            /*     onWheel: { */
            /*         if (wheel.modifiers & Qt.ControlModifier) { */
            /*             container.x += wheel.angleDelta.y */
            /*             console.log('wheel: ' + wheel.angleDelta.y) */
            /*             console.log('x: ' + container.x) */
            /*             /\* container.y = flick.contentY + (flick.height - container.height) / 2 *\/ */

            /*             /\* container.rotation += wheel.angleDelta.y / 120 * 5; *\/ */
            /*             /\* if (Math.abs(container.rotation) < 4){ *\/ */
            /*             /\*     container.rotation = 0; *\/ */
            /*             /\* } *\/ */
            /*         } else { */
            /*             container.rotation += wheel.angleDelta.x / 120; */
            /*             if (Math.abs(container.rotation) < 0.6){ */
            /*                 container.rotation = 0; */
            /*             } */
            /*             var scaleBefore = container.scale; */
            /*             container.scale += container.scale * wheel.angleDelta.y / 120 / 10; */
            /*         } */
            /*     } */
            /* } */
        }
    }
}
