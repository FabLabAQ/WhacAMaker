// The panel for joystick calibration. It instructions on top and a target in
// the centra part. Any click will go back to the previous panel
import QtQuick 2.0

AnimatedElementsPanel {
	id: container

	// The width of the label with instructions as a portion of the item
	// width
	property real labelWidth: 0.9
	// The height of the label with instructions as a portion of the item
	// height
	property real labelHeight: 0.1
	// If this is an item, when the back button is clicked this item is
	// hidden and backItem is shown. The end() signal is always emitted
	property var backItem: null
	// The size of the square targets
	property real targetSide: 20
	// The color of target
	property color targetColor: "black"

	// The signal emitted when calibration starts (i.e. this widget is made
	// visible)
	signal start()
	// The signal emitted when calibration ends (i.e. this widget is made
	// invisible)
	signal end()

	// The label describing what to do
	AnimatedLabel {
		id: label
		text: "Centra il joystick. Un pulsante o click del mouse esce"
		backgroundColor: "white"
		x: (container.width - width) / 2.0
		yWhenVisible: 0
		width: container.width * container.labelWidth
		height: container.height * container.labelHeight
	}

	// The central target
	AnimatedElement {
		id: centralTarget
		x: (container.width - width) / 2.0
		yWhenVisible: (container. height - height) / 2.0
		width: container.targetSide
		height: width

		Rectangle {
			anchors.fill: parent
			color: container.targetColor
			border.width: 0
		}
	}

	// The mouse area
	MouseArea {
		anchors.fill: parent
		onClicked: container.hideAll()
	}

	// The animated elements
	animatedElements: [label, centralTarget]

	// Called when all buttons have disappeared
	onAllDisappeared: {
		visible = false;
		if (backItem != null) {
			backItem.visible = true;
		}
	}

	// We need to reimplement this to send the calibrationStarted() signal
	// when the panel is shown
	onVisibleChanged: {
		if (visible) {
			start();
			showAll();
		} else {
			end();
		}
	}
}
