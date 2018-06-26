import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.1

Window {
    id: window
    visible: true
    width: 800
    height: 600
    color: "#e6e6e6"
    title: "Physic balls"

    signal addBall();
    signal removeBall();

    Item {
        id: container
        objectName: "container"
        anchors.rightMargin: 200
        anchors.fill: parent
        onChildrenChanged: ballsCount.text = "Balls count: " + container.children.length
    }

    Rectangle {
        id: menu
        objectName: "menu"
        x: 655
        width: 200
        color: "#ffffff"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Slider {
            id: timeScale
            objectName: "timeScale"
            x: 0
            y: 32
            width: 200
            height: 40
            stepSize: 0.1
            from: 0
            to: 4
            value: 1.0

            signal setTimeScale(double scale);

            onValueChanged: {
                setTimeScale(value);
                timeScaleValue.text = timeScale.value;
            }

            Label {
                id: label
                text: "Time scale"
                anchors.left: parent.left
                anchors.leftMargin: 5
                verticalAlignment: Text.AlignTop
                font.pointSize: 15
                anchors.top: parent.top
                anchors.topMargin: -24
            }

            Label {
                id: timeScaleValue
                objectName: "timeScaleValue"
                x: 5
                y: 5
                text: "1.0"
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.top: parent.top
                anchors.topMargin: -24
                verticalAlignment: Text.AlignTop
                font.pointSize: 15
            }
        }

        Button {
            id: resetTimeScale
            x: 50
            y: 78
            width: 124
            text: qsTr("Reset time scale")
            anchors.horizontalCenter: parent.horizontalCenter

            onPressed: timeScale.value = 1.;
        }

        Button {
            id: addBallButton
            y: 211
            height: 40
            text: qsTr("Add ball")
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: 5
            anchors.left: parent.left
            anchors.leftMargin: 5

            onPressed: {
                addBall();
            }
        }

        Button {
            id: removeBallButton
            y: 211
            height: 40
            text: qsTr("Remove ball")
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5

            onPressed: {
                removeBall();
            }
        }

        Button {
            id: removeAllBallsButton
            x: 155
            y: 257
            height: 40
            text: qsTr("Remove all balls")
            anchors.leftMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.left: parent.left

            onPressed: {
                while(container.children.length > 0)
                    removeBall();
            }
        }

        Text {
            id: ballsCount
            y: 181
            text: "Balls count: 0"
            font.family: "Arial"
            horizontalAlignment: Text.AlignHCenter
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15
            font.pixelSize: 20
        }
    }
}
