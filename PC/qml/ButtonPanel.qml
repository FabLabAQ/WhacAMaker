// This component allows creating a panel with buttons. All buttons are placed
// as items in an AnimatedElementsPanelWithItems and you must use the
// item-realated properties of AnimatedElementsPanelWithItems to set dimensions.
// This class provides a signal that is thrown when a button is pressed, with
// the button text as argument.
import QtQuick 2.0

AnimatedElementsPanelWithItems {
	id: container

	// Use itemHeight, itemWidth and itemSpacing to set dimensions.

	// If true adds a back button. When the back button is clicked the
	// goBack() signal is emitted. The back button is always the last button
	property bool addBackButton: true
	// The caption of the back button
	property string backButtonCaption: "Indietro"
	// If this is null when the back button is pressed the goBack signal is
	// raised, if this is an item, when the back button is clicked this item
	// is hidden and backItem is shown
	property var backItem: null
	// The list of buttons to add. Each element is a string with the button
	// caption
	property var buttonCaptions: []
	// The list of menus for each button. This should contain items, None
	// and can have less elements than buttonCaptions. When the i-th button
	// is clicked this list is checked. If i is greater than the number of
	// elements in this list or if buttonItems[i] is None the buttonClicked
	// signal is raised. Otherwise this item is hidden and the item at
	// buttonItems[i] is shown
	property var buttonItems: []

	// The signal emitted when a button is clicked. caption is the caption
	// of the button. This is emitted even if a function is already
	// connected to a button
	signal buttonClicked(string caption)
	// The signal emitted when the back button is clicked
	signal goBack()

	// The items vector is filled by the onButtonCaptionsChanged slot, the
	// buttons vector is empty
	buttons: []

	// An internal object needed to store the next item to show. This is
	// needed because we have to wait for buttons to go outside the screen
	// before showing the other panel
	QtObject {
		id: internalState

		// The item to show
		property var nextItem
	}

	// An internal function called when the back button is clicked
	function internalGoBack()
	{
		if (backItem == null) {
			goBack();
		} else {
			internalState.nextItem = backItem;
			hideAll();
		}
	}

	// An internal function called when a button is clicked
	function internalButtonClicked(buttonID)
	{
		if ((buttonID > buttonItems.length) || (buttonItems[buttonID] == null)) {
			buttonClicked(items[buttonID].caption);
		} else {
			internalState.nextItem = buttonItems[buttonID]
			hideAll();
		}
	}

	// Called when all buttons have disappeared
	onAllDisappeared: {
		visible = false;
		if (internalState.nextItem != null) {
			internalState.nextItem.visible = true;
		}
	}

	onButtonCaptionsChanged: {
		// Deleting old buttons
		for (button in items) {
			button.destroy()
		}
		items = []

		// Here we create all buttons but do not set their position
		for (var i = 0; i < buttonCaptions.length; i++) {
			var component = Qt.createComponent("Button.qml");
			var button = component.createObject(container, {"caption": buttonCaptions[i], "name": i});

			if (button == null) {
				console.log("Error creating button " + buttonCaptions[i]);
			}

			button.clicked.connect(internalButtonClicked);
			items.push(button);
		}

		// Creating the back button if we have to
		if (addBackButton) {
			var component = Qt.createComponent("Button.qml");
			var button = component.createObject(container, {"caption": backButtonCaption, "name": items.length, "onClicked": goBack()});

			if (button == null) {
				console.log("Error creating button " + buttonCaptions[i]);
			}

			button.clicked.connect(internalGoBack);
			items.push(button);
		}
	}
}
