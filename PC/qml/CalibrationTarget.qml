// A target in the calibration panel
import QtQuick 2.0

AnimatedElement {
	id: container

	// The color of the target
	property alias color: visualTarget.color
	// The size of the target borders as a potion of the item side
	property real borderWidth: 0.1
	// The color of the border
	property color borderColor: "black"

	Rectangle {
		id: visualTarget
		anchors.fill: parent
		border.width: container.width * container.borderWidth
		border.color: container.borderColor
	}
}
