import QtQuick 2.0

Item {
	id: container
	property string caption
	signal clicked()

	Rectangle {
		id: rectangle
		border.color: "white"
		anchors.fill: parent

		Text {
			id: buttonText
			text: container.caption
			anchors.horizontalCenter: rectangle.horizontalCenter
			anchors.verticalCenter: rectangle.verticalCenter
			font.pointSize: 24; font.bold: true
		}
	}

	MouseArea {
		anchors.fill: parent
		onClicked: container.clicked(container.cellColor)
	}
}
