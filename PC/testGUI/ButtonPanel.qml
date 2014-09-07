// This component allows creating a panel with buttons. You can specify the
// button captions, their width relative to the panel, their height (either
// relative or absolute) and the spacing between them. This class provdes a
// signal that is thrown when a button is pressed, with the button text as
// argument.
import QtQuick 2.0

Item {
	id: container

	// The width of buttons relative to the container width
	property real buttonWidth: 0.6
	// The height of buttons. If relativeHeight is true this is relative to
	// the component height, otherwise this is the actual height of buttons
	property real buttonHeight: 0.1
	// If true buttonHeight is relative to the component height, otherwise
	// buttonHeight is the actual height of buttons
	property bool relativeHeight: true
	// The spacing between buttons. This is relative to the button height
	property real buttonSpacing: 0.3
	// IF true adds a back button. When the back button is clicked the
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
	// The list of button objects. This is created at startup depending on
	// the list of button captions. This also contains the back button if
	// it has to be created
	property var buttons: []

	// The signal emitted when a button is clicked. caption is the caption
	// of the button. This is emitted even if a function is already
	// connected to a button
	signal buttonClicked(string caption)
	// The signal emitted when the back button is clicked
	signal goBack()

	// An internal object needed to store the next item to show. This is
	// needed because we have to wait for buttons to go outside the screen
	// before showing the other panel
	QtObject {
		id: internalState

		// The item to show
		property var nextItem
	}

	// The function to compute the width in pixels of buttons
	function computeButtonWidth()
	{
		return width * buttonWidth;
	}

	// The function to compute the height in pixels of buttons
	function computeButtonHeight()
	{
		if (relativeHeight) {
			return height * buttonHeight;
		} else {
			return buttonHeight;
		}
	}

	// The function to compute the spacing between buttons
	function computeButtonSpacing()
	{
		return computeButtonHeight() * buttonSpacing;
	}

	// Shows all button. This changes their state to "appearing" so that
	// they are animated
	function showAllButtons()
	{
		for (var i = 0; i < buttons.length; i++) {
			buttons[i].state = "appearing";
		}
	}

	// Hides all button. This changes their state to "disappearing" so that
	// they are animated. Each button sends a disappeared signal when the
	// animation is finished
	function hideAllButtons()
	{
		for (var i = 0; i < buttons.length; i++) {
			buttons[i].state = "disappearing";
		}
	}

	// The function to set the buttons position and size
	function setButtonPositionAndSize()
	{
		if (buttons.length == 0) {
			return;
		}

		// Computing dimensions of buttons
		var bw = computeButtonWidth();
		var bh = computeButtonHeight();
		var bs = computeButtonSpacing();

		// Computing the total space taken by buttons
		var totalButtonSpace = bh * buttons.length;
		if (buttons.length != 1) {
			totalButtonSpace += bs * (buttons.length - 1);
		}

		// Computing the x position of buttons (the same for all buttons) and the y position
		// of the first button
		var xPos = (width - bw) / 2;
		var firstYPos = (height - totalButtonSpace) / 2;
		var bx = [xPos];
		var by = [firstYPos];

		for (var i = 1; i < buttons.length; i++) {
			bx.push(xPos);
			by.push(by[i - 1] + bh + bs);
		}

		// Now we can set button position and sizes
		for (var i = 0; i < buttons.length; i++) {
			buttons[i].x = bx[i];
			buttons[i].yWhenVisible = by[i];
			buttons[i].yWhenInvisible = -bh;
			buttons[i].width = bw;
			buttons[i].height =  bh;
		}
	}

	// An internal function called when the back button is clicked
	function internalGoBack()
	{
		if (backItem == null) {
			goBack();
		} else {
			internalState.nextItem = backItem;
			hideAllButtons();
		}
	}

	// An internal function called when a button is clicked
	function internalButtonClicked(buttonID)
	{
		if ((buttonID > buttonItems.length) || (buttonItems[buttonID] == null)) {
			buttonClicked(buttons[buttonID].caption);
		} else {
			internalState.nextItem = buttonItems[buttonID]
			hideAllButtons();
		}
	}

	// The function called when a button has disappeared. If all buttons have disappeared
	// this function hides this item
	function internalButtonDisappeared(buttonID)
	{
		var allDisappeared = true;
		for (var i = 0; i < buttons.length; i++) {
			if (buttons[i].visible == true) {
				allDisappeared = false;
				break;
			}
		}

		if (allDisappeared) {
			visible = false;
			if (internalState.nextItem != null) {
				internalState.nextItem.visible = true;
			}
		}
	}

	onButtonCaptionsChanged: {
		// Deleting old buttons
		for (button in buttons) {
			button.destroy()
		}
		buttons = []

		// Here we create all buttons but do not set their position
		for (var i = 0; i < buttonCaptions.length; i++) {
			var component = Qt.createComponent("Button.qml");
			var button = component.createObject(container, {"caption": buttonCaptions[i], "buttonID": i});

			if (button == null) {
				console.log("Error creating button " + buttonCaptions[i]);
			}

			button.clicked.connect(internalButtonClicked);
			button.disappeared.connect(internalButtonDisappeared);
			buttons.push(button);
		}

		// Creating the back button if we have to
		if (addBackButton) {
			var component = Qt.createComponent("Button.qml");
			var button = component.createObject(container, {"caption": backButtonCaption, "buttonID": buttons.length, "onClicked": goBack()});

			if (button == null) {
				console.log("Error creating button " + buttonCaptions[i]);
			}

			button.clicked.connect(internalGoBack);
			button.disappeared.connect(internalButtonDisappeared);
			buttons.push(button);
		}
	}

	Component.onCompleted: {
		setButtonPositionAndSize();
		if (visible) {
			showAllButtons()
		}
	}

	onWidthChanged: setButtonPositionAndSize()
	onHeightChanged: setButtonPositionAndSize()

	onVisibleChanged: {
		if (visible) {
			showAllButtons();
		}
	}
}
