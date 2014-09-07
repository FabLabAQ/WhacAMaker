// A simple component with a text label and a text input
import QtQuick 2.0

Item {
	id: container

	// The description of the input field
	property alias label: textLabel.text
	// The validator for entered text
	property alias validator: textInput.validator
	// The entered text
	property alias text: textInput.text
	// True if the entered text is valid
	property alias acceptableInput: textInput.acceptableInput
	// The proportion of the label with respect to the input field
	property real labelInputProportion: 0.5
	// The space between the text area and the label
	property real spacing: 10
	// The y position to reach when the input field is visible (x stays the
	// same)
	property int yWhenVisible
	// The y position to reach when the input field is invisible (x stays
	// the same)
	property int yWhenInvisible
	// The id of the input field. This value is the parameter used by the
	// disappeard signal
	property var inputFieldID

	// The signal emitted when the input field has disappeared. The
	// parameter i is the field
	signal disappeared(var i)

	Text {
		id: textLabel
		x: 0
		y: 0
		width: (container.width - container.spacing) * (container.labelInputProportion / (1 + container.labelInputProportion))
		height: container.height
		horizontalAlignment: Text.AlignRight
		verticalAlignment: Text.AlignVCenter
		font { pointSize: 24; bold: true }
	}

	Rectangle {
		id: textInputBackground
		x: textLabel.width + container.spacing
		y: 0
		width: container.width - container.spacing - textLabel.width
		height: container.height

		TextInput {
			id: textInput
			anchors.fill: parent
			horizontalAlignment: Text.AlignLeft
			verticalAlignment: Text.AlignVCenter
			clip: true
			font { pointSize: 24; bold: true }
		}
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
					script: container.disappeared(container.inputFieldID)
				}
			}
		}
	]
}
