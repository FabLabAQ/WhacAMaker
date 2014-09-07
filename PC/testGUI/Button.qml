// A simple button used in the game. This also contains animations to make the
// button appear/disappear
import QtQuick 2.0

Item {
	id: container
	// The caption of the button
	property string caption: "Button"
	// The y position to reach when the button is visible (x stays the same)
	property int yWhenVisible
	// The y position to reach when the button is invisible (x stays the
	// same)
	property int yWhenInvisible
	// The id of the button. This value is the parameter used by the clicked
	// and disappeared signals
	property var buttonID

	// The signal emitted when the button is clicked. The parameter i is the
	// buttonID
	signal clicked(var i)
	// The signal emitted when the button has disappeared. The parameter i
	// is the buttonID
	signal disappeared(var i)

	Rectangle {
		id: rectangle
		border.color: "white"
		anchors.fill: parent

		Text {
			id: buttonText
			text: container.caption
			anchors { horizontalCenter: rectangle.horizontalCenter; verticalCenter: rectangle.verticalCenter }
			font { pointSize: 24; bold: true }
		}
	}

	MouseArea {
		anchors.fill: parent
		onClicked: container.clicked(container.buttonID)
	}

	states: [
		State {
			name: "appearing"
		},
		State {
			name: "disappearing"
		}
	]

	transitions: [
		Transition {
			from: "*"
			to: "appearing"

			SequentialAnimation {
				PropertyAction {
					target: container
					property: "y"
					value: container.yWhenInvisible
				}
				PropertyAction {
					target: container
					property: "visible"
					value: true
				}
				NumberAnimation {
					target: container
					properties: "y"
					to: container.yWhenVisible
					duration: 500;
					easing.type: Easing.InOutQuad
				}
			}
		},
		Transition {
			from: "*"
			to: "disappearing"

			SequentialAnimation {
				PropertyAction {
					target: container
					property: "y"
					value: container.yWhenVisible
				}
				NumberAnimation {
					target: container
					properties: "y"
					to: container.yWhenInvisible
					duration: 500;
					easing.type: Easing.InOutQuad
				}
				PropertyAction {
					target: container
					property: "visible"
					value: false
				}
				ScriptAction {
					script: container.disappeared(container.buttonID)
				}
			}
		}
	]
}
