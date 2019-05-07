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

                // This needs to be a child of PinchArea, otherwise it
                // will eat up press evens
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
            }
        }
    }
}
