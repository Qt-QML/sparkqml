/* Sample1.qml

  1) Simple structure. No dependence to other component
  2) No list structure
 */
import QtQuick 2.0

Item {
    id: sample1
    x: 10
    y: 10
    width: 640
    height: 480

    Item {
        id: item1
        anchors.fill: parent
    }

    Item {
        id: item2
        width: 100
        height: 100
        anchors.right: parent.right
    }

    Rectangle {
        id: item3
        width: 100
        height: 100
    }

    Text {
        id: item4
    }
}
