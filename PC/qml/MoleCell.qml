// A single cell containing the mole. The cell is square, has a uniform color
// and a border. This has two states: default and "spotOn"
import QtQuick 2.3
import WhacAMaker 1.0

AnimatedElement {
	id: container

	// The index of the cell
	property int index
	// The size of the cell
	property real size
	// The background color
	property color backgroundColor: "black" // "darkGray"
	// The color of the border
	property color borderColor: "black"
	// The radius of the corner of the rectangle border as a percentage of
	// the size
	property real radius: 0 // 0.05
	// The size of the spot (its diameter) as a portion of the size of the
	// cell
	property real spotSize: 1.0 // 0.6
	// The color of the spot
	property alias spotColor: spot.color
	// The starting angle of the spot
	property alias spotAngle: spot.angle
	// The size of the circle (its diameter) as a portion of the size of the
	// cell
	property real circleSize: 0.45
	// Set to true if the joystick is on this cells
	property bool pointed: false
	// Set to true to show the spot
	property bool spotOn: false
	// Set to true when a mole is hit
	property bool moleHit: false
	// Set to true when the wrong mole is hit
	property bool moleWrongHit: false
	// Set to true when the user missed the mole
	property bool moleMissed: false
	// Width and height are equal to size
	width: size
	height: size

	onMoleHitChanged: {
		if (moleHit) {
			hitAnimation.start();
			moleHit = false;
		}
	}

	onMoleWrongHitChanged: {
		if (moleWrongHit) {
			wrongHitAnimation.start();
			moleWrongHit = false;
		}
	}

	onMoleMissedChanged: {
		if (moleMissed) {
			missAnimation.start();
			moleMissed = false;
		}
	}

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

	// The spot "illuminating" the mole. This is on when spotOn is true
	MoleSpot {
		id: spot

		anchors.fill: parent
		z: 20
		angle: 0
		color: "yellow"
		visible: container.spotOn
		spotSize: container.circleSize

		// The animation rotating the spot. The property being animated is Item.rotation,
		// angle can be used to set the starting angle
		RotationAnimator {
			id: animation

			from: 0
			to: 360
			duration: 1000
			loops: Animation.Infinite
			paused: !container.visible
			target: spot
			running: true
		}
	}

	// The joystick pointer. This is visible only when the joystick pointer
	// is on this cell
	Rectangle {
		id: pointer

		width: container.size * container.spotSize
		height: container.size * container.spotSize
		x: (container.width - width) / 2.0
		y: (container.height - height) / 2.0
		color: "white" // "red"
		border.width: 0
		z: 10
		opacity: 1.0 // 0.5
		visible: container.pointed
	}

	Rectangle {
		id: hitSignal

		width: container.size * container.spotSize
		height: container.size * container.spotSize
		x: (container.width - width) / 2.0
		y: (container.height - height) / 2.0
		color: "red"
		border.width: 0
		z: 30
		opacity: 0.0
		visible: true

		SequentialAnimation {
			id: hitAnimation

			NumberAnimation {
				from: 1
				to: 0
				target: hitSignal
				property: "opacity"
				duration: 1000
			}
		}
	}

	Rectangle {
		id: wrongHitSignal

		width: container.size * container.spotSize
		height: container.size * container.spotSize
		x: (container.width - width) / 2.0
		y: (container.height - height) / 2.0
		color: "green"
		border.width: 0
		z: 30
		opacity: 0.0
		visible: true

		SequentialAnimation {
			id: wrongHitAnimation

			NumberAnimation {
				from: 1
				to: 0
				target: wrongHitSignal
				property: "opacity"
				duration: 1000
			}
		}
	}

	Rectangle {
		id: missSignal

		width: container.size * container.spotSize
		height: container.size * container.spotSize
		x: (container.width - width) / 2.0
		y: (container.height - height) / 2.0
		color: "blue"
		border.width: 0
		z: 30
		opacity: 0.0
		visible: true

		SequentialAnimation {
			id: missAnimation

			NumberAnimation {
				from: 1
				to: 0
				target: missSignal
				property: "opacity"
				duration: 1000
			}
		}
	}
}
