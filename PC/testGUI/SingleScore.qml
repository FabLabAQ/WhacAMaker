// A simple component showing a single score
import QtQuick 2.0

AnimatedElement {
	id: container

	// The rank of the score
	property int rank
	// The name of the player
	property string playerName
	// The score
	property real score

// 	// The description of the input field
// 	property alias label: textLabel.text
// 	// The validator for entered text
// 	property alias validator: textInput.validator
// 	// The entered text
// 	property alias text: textInput.text
// 	// True if the entered text is valid
// 	property alias acceptableInput: textInput.acceptableInput
// 	// The proportion of the label with respect to the input field
// 	property real labelInputProportion: 0.5
// 	// The space between the text area and the label
// 	property real spacing: 10
//
// 	Text {
// 		id: textLabel
// 		x: 0
// 		y: 0
// 		width: (container.width - container.spacing) * (container.labelInputProportion / (1 + container.labelInputProportion))
// 		height: container.height
// 		horizontalAlignment: Text.AlignRight
// 		verticalAlignment: Text.AlignVCenter
// 		font { pointSize: 24; bold: true }
// 	}
//
// 	Rectangle {
// 		id: textInputBackground
// 		x: textLabel.width + container.spacing
// 		y: 0
// 		width: container.width - container.spacing - textLabel.width
// 		height: container.height
//
// 		TextInput {
// 			id: textInput
// 			anchors.fill: parent
// 			horizontalAlignment: Text.AlignLeft
// 			verticalAlignment: Text.AlignVCenter
// 			clip: true
// 			font { pointSize: 24; bold: true }
// 		}
// 	}
}
