// A container for AnimatedElements with functions to show all elements or hide
// them all
import QtQuick 2.0

Item {
	id: container

	// The list of elements to animate. All elements should inherit from
	// AnimatedElement
	property var animatedElements: []

	// The signal emitted then all elements have disappeared
	signal allDisappeared()
	// The signal emitted then all elements have appeared
	signal allAppeared()

	// An object to keep an internal state. This is used to keep track of
	// which element has appeared/disappeared
	QtObject {
		id: internalState

		// The list of objects that have appeared/disappeared
		property var elementsEndedAnimation: []
	}

	// An internal function called when controls appear. If all elements
	// have appeared, emits the allAppeared() signal
	function internalAppeared(obj)
	{
		internalState.elementsEndedAnimation[obj] = true;

		if (internalState.elementsEndedAnimation.length == animatedElements.length) {
			internalState.elementsEndedAnimation = [];

			// All elements have appeared, we can emit the allAppeared() signal
			allAppeared();
		}
	}

	// An internal function called when controls disappear. If all elements
	// have appeared, emits the allAppeared() signal
	function internalDisappeared(obj)
	{
		internalState.elementsEndedAnimation[obj] = true;

		if (internalState.elementsEndedAnimation.length == animatedElements.length) {
			internalState.elementsEndedAnimation = [];

			// All elements have appeared, we can emit the allDisappeared() signal
			allDisappeared();
		}
	}

	// A function to show all controls
	function showAll()
	{
		for (var i = 0; i < animatedElements.length; i++) {
			animatedElements[i].state = "appearing";
		}
	}

	// A function to hide all controls
	function hideAll()
	{
		for (var i = 0; i < animatedElements.length; i++) {
			animatedElements[i].state = "disappearing";
		}
	}

	Component.onCompleted: {
		if (visible) {
			showAll()
		}
	}

	onVisibleChanged: {
		if (visible) {
			showAll();
		}
	}
}
