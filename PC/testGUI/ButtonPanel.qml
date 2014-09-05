// This component allows creating a panel with buttons. You can specify the
// button captions, their width relative to the panel, their height (either
// relative or absolute) and the spacing between them. This class provdes a
// signal that is thrown when a button is pressed, with the button text as
// argument
import QtQuick 2.0

Rectangle {
	id: container
	color: "lightgray"

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
	// The list of buttons to add. Each element is a string with the button
	// caption
	property var buttonCaptions: []
	// The list of button objects. This is created at startup depending on
	// the list of button captions. This also contains the back button if
	// it has to be created
	property var buttons: []

	// The function to compute the width in pixels of buttons
	function computeButtonWidth()
	{
		return container.width * container.buttonWidth;
	}

	// The function to compute the height in pixels of buttons
	function computeButtonHeight()
	{
		if (container.relativeHeight) {
			return container.height * container.buttonHeight;
		} else {
			return container.buttonHeight;
		}
	}

	// The function to compute the spacing between buttons
	function computeButtonSpacing()
	{
		return container.computeButtonHeight() * container.buttonSpacing;
	}

	// The function to set the buttons position and size
	function setButtonPositionAndSize()
	{
		if (buttons.length == 0) {
			return;
		}

		// Computing dimensions of buttons
		var bw = container.computeButtonWidth();
		var bh = container.computeButtonHeight();
		var bs = container.computeButtonSpacing();

		// Computing the total space taken by buttons
		var totalButtonSpace = bh * container.buttons.length;
		if (container.buttons.length != 1) {
			totalButtonSpace += bs * (container.buttons.length - 1);
		}

		// Computing the x position of buttons (the same for all buttons) and the y position
		// of the first button
		var xPos = (container.width - bw) / 2;
		var firstYPos = (container.height - totalButtonSpace) / 2;
		var bx = [xPos];
		var by = [firstYPos];

		for (var i = 1; i < container.buttons.length; i++) {
			bx.push(xPos);
			by.push(by[i - 1] + bh + bs);
		}

		// Now we can set button position and sizes create buttons
		for (var i = 0; i < container.buttons.length; i++) {
			container.buttons[i].x = bx[i];
			container.buttons[i].y = -bh;
			container.buttons[i].yWhenVisible = by[i];
			container.buttons[i].width = bw;
			container.buttons[i].height =  bh;
		}
	}

	// The signal emitted when a button is clicked. caption is the caption
	// of the buttton
	signal buttonClicked(string caption)
	// The signal emitted when the back button is clicked
	signal goBack()

	onButtonCaptionsChanged: {
		container.buttons = []

		// Here we create all buttons but do not set their position
		for (var i = 0; i < container.buttonCaptions.length; i++) {
			var component = Qt.createComponent("Button.qml");
			var button = component.createObject(container, {"caption": container.buttonCaptions[i]});

			if (button == null) {
				console.log("Error creating button " + container.buttonCaptions[i]);
			}

			button.clicked.connect(container.buttonClicked);
			container.buttons.push(button);
		}

		// Creating the back button if we have to
		if (container.addBackButton) {
			var component = Qt.createComponent("Button.qml");
			var button = component.createObject(container, {"caption": container.backButtonCaption, "onClicked": container.goBack()});

			if (button == null) {
				console.log("Error creating button " + container.buttonCaptions[i]);
			}

			button.clicked.connect(container.goBack);
			container.buttons.push(button);
		}

// 		CERCARE ANCHE SE ESISTE UNA MAPPA IN CUI MEMORIZZARE LA RELAZIONE caption (string) -> Button object
	}

	Component.onCompleted: setButtonPositionAndSize()

	onVisibleChanged: setButtonPositionAndSize()
}
