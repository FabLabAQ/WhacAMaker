import QtQuick 2.0

Rectangle {
	id: rectangle
	border.color: "red"
	anchors.fill: parent

	signal goBack

	Text {
		id: buttonText
		text: "Play Game!"
		anchors.horizontalCenter: rectangle.horizontalCenter
		anchors.verticalCenter: rectangle.verticalCenter
		font.pointSize: 24; font.bold: true
	}

	MouseArea {
		anchors.fill: parent
		onClicked: rectangle.goBack()
	}
}
