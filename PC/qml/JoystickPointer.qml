// A pointer for the joystick. This has z equal to 10 to be on top of other
// items. The x and y position indicate the center of the pointer (i.e. the
// pointed pixel). The various states indicate the shape and size of the
// pointer. Availabel states/pointers are:
// 	- "": normal, used in menus
// 	- "game": used during the game
// 	- "calibration": used during calibration
import QtQuick 2.0

Item {
	id: container
	x: 0
	y: 0
	// z is 10 to be above everything else
	z: 10
	width: pointerNormal.width
	height: pointerNormal.height

	// The function that takes the status of joystick buttons
	function joystickButtonStates(button1Pressed, button2Pressed)
	{
		// console.log("Button1: " + button1Pressed + ", Button2: " + button2Pressed);
	}

	// The pointer in "" status
// 	Rectangle {
// 		id: pointerNormal
// 		x: -width / 2.0;
// 		y: -height / 2.0;
// 		width: 10
// 		height: 10
// 		opacity: 0.5
// 		color: "green"
// 		visible: true
// 	}
	AnimatedImage {
		id: pointerNormal
		x: -width / 2.0;
		y: -height / 2.0;
		width: 100
		height: 100
		opacity: 0.8
		visible: true
		playing: true
		source: "qrc:///worm.gif"
// 		source: "qrc:///bball.png"
// 		source: "qrc:///soccer_ball_animated.svg"
// 		source: "qrc:///Rotating_earth.gif"
	}

	// The pointer in "calibration" status
	Rectangle {
		id: pointerCalibration
		x: -width / 2.0;
		y: -height / 2.0;
		width: 10 // questo deve dipendere dalla grandezza del target per la calibrazione
		height: 10
		opacity: 0.5
		color: "green"
		visible: false
	}

	// The pointer in "game" status
	Rectangle {
		id: pointerGame
		x: -width / 2.0;
		y: -height / 2.0;
		width: 10
		height: 10
		opacity: 0.5
		color: "red"
		visible: false
	}

	states: [
		State {
			name: "game"

			PropertyChanges { target: pointerNormal; visible: false }
			PropertyChanges { target: pointerCalibration; visible: false }
			PropertyChanges { target: pointerGame; visible: true }
			PropertyChanges { target: container; width: pointerGame.width; height: pointerGame.height }
		},
		State {
			name: "calibration"

			PropertyChanges { target: pointerNormal; visible: false }
			PropertyChanges { target: pointerCalibration; visible: true }
			PropertyChanges { target: pointerGame; visible: false }
			PropertyChanges { target: container; width: pointerCalibration.width; height: pointerCalibration.height }
		}
	]
}
