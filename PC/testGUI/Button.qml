// A simple button used in the game
import QtQuick 2.0

Item {
	id: container
	// The caption of the button
	property string caption
	// The y position to reach when the button is visible (x stays the same)
	property int yWhenVisible
	// The id of the button. This value is the parameter used by the clicked
	// signal
	property int buttonID

	// The signal emitted when the button is clicked. The parameter i is the
	// buttonID
	signal clicked(int i)

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
		onClicked: container.clicked(container.buttonID)
	}

	states: State {
		name: "appearing"
		when: container.visible == true

		PropertyChanges {
			target: container
			y: container.yWhenVisible
		}
	}

	transitions: Transition {
		from: ""; to: "appearing"; reversible: true

		NumberAnimation {
			properties: "y";
			duration: 500;
			easing.type: Easing.InOutQuad
		}
	}
}
