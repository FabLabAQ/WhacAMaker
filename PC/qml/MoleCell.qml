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

	// The spot "illuminating" the mole. This is on when state is "spotOn"
	Canvas {
		id: spot

		anchors.fill: parent
		contextType: "2d";
		renderStrategy: Canvas.Threaded;
		renderTarget: Canvas.Image;
		antialiasing: true;
		smooth: true;
		visible: false
		// The current angle of the rotating circle
		property real angle: 0
		// The width of the rotating circle line
		property real lineWidth: 4
		// The color of the line of the rotating line
		property color lineColor: "blue"

		// The animation on the angle property to have a rotating circle
		NumberAnimation on angle {
			id: animation

			from: 0
			to: 2 * Math.PI
			duration: 1000
			loops: Animation.Infinite
			paused: !container.visible
		}

		// The code to paint
		onPaint: {
			if (context) {
				context.clearRect(0, 0, width, height);

				// Creating the arc path
				context.beginPath();
				context.arc(x + width / 2.0, y + height / 2.0, (container.size * container.spotSize) / 2.0, angle, angle + 1.5 * Math.PI);

				// Stroking it
				context.lineWidth = lineWidth;
				context.strokeStyle = lineColor;
				context.stroke();
			}
		}

		onAngleChanged: requestPaint()
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
			PropertyChanges { target: spot; visible: true }
		}
	]
}
