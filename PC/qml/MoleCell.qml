// A single cell containing the mole. The cell is square, has a uniform color
// and a border. This has two states: default and "spotOn"
import QtQuick 2.0

AnimatedElement {
	id: container

	// The index of the cell
	property int index
	// The size of the cell
	property real size
	// The background color
	property color backgroundColor: "darkGray"
	// The color of the border
	property color borderColor: "black"
	// The radius of the corner of the rectangle border as a percentage of
	// the size
	property real radius: 0.05
	// The size of the spot (its diameter) as a portion of the size of the
	// cell
	property real spotSize: 0.6
	// Set to true tf the joystick is on this cells
	property bool pointed: false
	// Width and height are equal to size
	width: size
	height: size

	// The actual rectangle
	Rectangle {
		id: rectangle

		anchors.fill: parent
		color: container.backgroundColor
		border.color: container.borderColor
		border.width: 2
		radius: container.size * container.radius
		antialiasing: true
	}

	// The spot "illuminating" the mole. This is on when state is "spotOn",
	// in default state its opacity is 0
	Rectangle {
		id: spot

		width: container.size * container.spotSize
		height: container.size * container.spotSize
		x: (container.width - width) / 2.0
		y: (container.height - height) / 2.0
		color: "white"
		border.width: 0
		radius: width / 2
		z: 10
		opacity: 0
	}

	// The joystick pointer. This is visible only when the joystick pointer
	// is on this cell
	Rectangle {
		id: pointer

		width: container.size * container.spotSize
		height: container.size * container.spotSize
		x: (container.width - width) / 2.0
		y: (container.height - height) / 2.0
		color: "red"
		border.width: 0
		z: 20
		opacity: 0.5
		visible: container.pointed
	}

	states: [
		State {
			name: "spotOn"
			PropertyChanges { target: spot; opacity: 1 }
		}
	]

	transitions: [
		Transition {
			from: "*"
			to: "*"

			NumberAnimation {
				target: spot
				properties: "opacity"
				duration: 100;
				easing.type: Easing.InOutQuad
			}
		}
	]
}
