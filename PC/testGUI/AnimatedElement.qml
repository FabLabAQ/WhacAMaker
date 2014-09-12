// A simple component used in the game. This contains code for animations and
// two sates which can be used to trigger animations, "appearing" and
// "disappearing". This also has a signal that is emitted when the disappearing
// animation is finished.
import QtQuick 2.0

Item {
	id: container
	// The y position to reach when the button is visible (x stays the same)
	property int yWhenVisible
	// The y position to reach when the button is invisible (x stays the
	// same)
	property int yWhenInvisible: -height
	// The name of this elements (can be used to identify this item)
	property var name

	// The signal emitted when the component has disappeared
	signal disappeared()
	// The signal emitted when the component has appeared
	signal appeared()

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
				ScriptAction {
					script: container.appeared()
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
					script: container.disappeared()
				}
			}
		}
	]
}
