// A simple component used in the game. This contains code for animations and
// two sates which can be used to trigger animations, "appearing" and
// "disappearing". This also has a signal that is emitted when the disappearing
// animation is finished
import QtQuick 2.0

Item {
	id: container
	// The y position to reach when the button is visible (x stays the same)
	property int yWhenVisible
	// The y position to reach when the button is invisible (x stays the
	// same)
	property int yWhenInvisible
	// The id of the component. This value is the parameter used by the
	// disappeared signals
	property var componentID

	// The signal emitted when the component has disappeared. The parameter
	// i is the componentID
	signal disappeared(var i)

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
					script: container.disappeared(container.componentID)
				}
			}
		}
	]
}
