// A simple label inheriting from AnimatedElement
import QtQuick 2.0

AnimatedElement {
	id: container

	// The text to show
	property alias text: buttonText.text

	Rectangle {
		id: rectangle
		border.color: "white"
		anchors.fill: parent

		Text {
			id: buttonText
			anchors { horizontalCenter: rectangle.horizontalCenter; verticalCenter: rectangle.verticalCenter }
			font { pointSize: 24; bold: true }
		}
	}
}
