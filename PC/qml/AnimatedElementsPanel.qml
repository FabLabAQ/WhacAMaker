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
		property int elementsEndedAnimation: 0
		// The list of objects previously connected, to remove
		// connections before connecting the new ones
		property var oldAnimatedElements: []
	}

	// An internal function called when controls appear. If all elements
	// have appeared, emits the allAppeared() signal
	function internalAppeared()
	{
		internalState.elementsEndedAnimation++;

		if (internalState.elementsEndedAnimation == animatedElements.length) {
			internalState.elementsEndedAnimation = 0;

			// All elements have appeared, we can emit the allAppeared() signal
			allAppeared();
		}
	}

	// An internal function called when controls disappear. If all elements
	// have appeared, emits the allAppeared() signal
	function internalDisappeared()
	{
		internalState.elementsEndedAnimation++;

		if (internalState.elementsEndedAnimation == animatedElements.length) {
			internalState.elementsEndedAnimation = 0;

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

	// A function to connect signals from animated elements
	function internalConnectAnimatedElementsSignals()
	{
		// Removing old connections
		for (var i = 0; i < internalState.oldAnimatedElements.length; i++) {
			internalState.oldAnimatedElements[i].disappeared.disconnect(internalDisappeared);
			internalState.oldAnimatedElements[i].appeared.disconnect(internalAppeared);
		}

		internalState.oldAnimatedElements = [];

		// Creating new connections
		for (var i = 0; i < animatedElements.length; i++) {
			animatedElements[i].disappeared.connect(internalDisappeared);
			animatedElements[i].appeared.connect(internalAppeared);
			// We do it here to do a deep copy
			internalState.oldAnimatedElements.push(animatedElements[i]);
		}
	}

	onAnimatedElementsChanged: {
		internalConnectAnimatedElementsSignals();
	}

	Component.onCompleted: {
		if (visible) {
			showAll();
		}
	}

	onVisibleChanged: {
		if (visible) {
			showAll();
		}
	}

	// This is to update positions when the item is resized
	onHeightChanged: {
		if (visible) {
			for (var i = 0; i < animatedElements.length; i++) {
				animatedElements[i].y = animatedElements[i].yWhenVisible;
			}
		}
	}
}
