// A keyboard on screen. This has three signals: one emitted every time the
// button of a character is clicked, one for backspace and one for enter.
// Buttons are in 4 rows with 10 buttons each
import QtQuick 2.0

AnimatedElement {
	id: container

	// The spacing between buttons as a portion of button width
	property real buttonSpacing: 0.1
	// The external border as a portion of button width
	property real externalBorder: 0.05
	// The preferred height of the keyboard (this is set by placeButtons())
	property real preferredHeight

	// The signal emitted when the backspace button is clicked
	signal backspace()
	// The signal emitted when the enter button is clicked
	signal enter()
	// The signal emitted when a character is pressed. c is the caracter
	signal keyPressed(string c)

	// An object with internal variables
	QtObject {
		id: internalVars

		// The list of all buttons
		property var buttons: []
	}

	// The function called when a button is pressed
	function internalKeyPressed(k)
	{
		if (k == "Bks") {
			backspace();
		} else if (k == "Ent") {
			enter();
		} else {
			keyPressed(k);
		}
	}

	// Creates all buttons
	function createButtons()
	{
		var captions = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
		                "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
		                "A", "S", "D", "F", "G", "H", "J", "K", "L", "Ent",
		                "Z", "X", "C", "V", "B", "N", "M", ".", "-", "Bks"];

		// Deleting old buttons
		for (button in internalVars.buttons) {
			button.destroy();
		}
		internalVars.buttons = [];

		// Here we only create the buttons, without placing them
		for (var i = 0; i < captions.length; i++) {
			var component = Qt.createComponent("Button.qml");
			var button = component.createObject(container, {"caption": captions[i], "name": captions[i]});

			if (button == null) {
				console.log("Error creating button " + caption);
			}

			button.clicked.connect(internalKeyPressed);
			internalVars.buttons.push(button);
		}
	}

	// Places all buttons. This function expects all 40 buttons to already
	// exists in the internalVars,buttons. This also changes the keyboard
	// height so that it is the correct one
	function placeButtons()
	{
		if (!Array.isArray(internalVars.buttons) || (internalVars.buttons.length != 40)) {
			return;
		}

		// Computing sizes (buttons are square)
		var buttonDim = width / (10.0 + 9 * buttonSpacing + 2 * externalBorder);
		var absButtonSpacing = buttonDim * buttonSpacing;
		var absExternalBorder = buttonDim * externalBorder;

		// Changing the keyboard height
		preferredHeight = 4 * buttonDim + 3 * absButtonSpacing + 2 * absExternalBorder;

		// Now placing buttons
		var curY = absExternalBorder;
		for (var row = 0; row < 4; row++) {
			var curX = absExternalBorder;
			for (var col = 0; col < 10; col++) {
				var b = internalVars.buttons[col + 10 * row];
				b.x = curX;
				b.y = curY;
				b.width = buttonDim;
				b.height = buttonDim;

				curX += buttonDim + absButtonSpacing;
			}
			curY += buttonDim + absButtonSpacing;
		}
	}

	// When the size of the container changes, we have to recompute the
	// positions of buttons
	onWidthChanged: placeButtons()
	onHeightChanged: placeButtons()

	Component.onCompleted: {
		createButtons();
		placeButtons();
	}
}
