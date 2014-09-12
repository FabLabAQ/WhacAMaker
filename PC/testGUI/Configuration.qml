// The panel with configuration options
import QtQuick 2.0

AnimatedElementsPanelWithItems {
	id: container
	// The panel to show when back or save are clicked. If this is null only
	// the save or goBack signals are raised
	property var panelToShow: null

	// The width of input fields relative to the container width
	property alias inputFieldsWidth: container.itemWidth
	// The height of input fields relative to the component height
	property alias inputFieldsHeight: container.itemHeight
	// The spacing between input fields. This is relative to the input
	// fields height
	property alias inputFieldsSpacing: container.itemSpacing
	// The proportion of the label with respect to the input field
	property real labelInputProportion: 0.5
	// The space between the text area and the label
	property real labelInputSpacing: 10

	// The signal emitted when the save button is clicked
	signal save()
	// The signal emitted when the back button is clicked
	signal goBack()

	// Adding input fields: usb port...
	InputField {
		id: serialPort
		label: "Porta seriale Gioco:"
		labelInputProportion: container.labelInputProportion
		spacing: container.labelInputSpacing
	}

	// ... distance from screen...
	InputField {
		id: screenDistance
		label: "Distanza dallo schermo:"
		labelInputProportion: container.labelInputProportion
		spacing: container.labelInputSpacing
		validator: DoubleValidator { bottom: 0 }
	}

	// ... vertical distance from screen center...
	InputField {
		id: verticalScreenCenterDistance
		label: "Distanza verticale dal centro dello schermo:"
		labelInputProportion: container.labelInputProportion
		spacing: container.labelInputSpacing
		validator: DoubleValidator {}
	}

	// ... and horizontal distance from screen center.
	InputField {
		id: horizontalScreenCenterDistance
		label: "Distanza orizzontale dal centro dello schermo:"
		labelInputProportion: container.labelInputProportion
		spacing: container.labelInputSpacing
		validator: DoubleValidator {}
	}

	// Now adding the buttons to save...
	Button {
		id: saveButton
		caption: "Salva"

		onClicked: {
			save();
			if (panelToShow != null) {
				hideAll();
			}
		}
	}

	// ... and to go back.
	Button {
		id: backButton
		caption: "Indietro"

		onClicked: {
			goBack();
			if (panelToShow != null) {
				hideAll();
			}
		}
	}

	// The list of items and buttons
	items: [serialPort, screenDistance, verticalScreenCenterDistance, horizontalScreenCenterDistance]
	buttons: [saveButton, backButton]

	// The function called when all elements have disappeared
	onAllDisappeared: {
		visible = false;
		if (panelToShow != null) {
			panelToShow.visible = true;
		}
	}
}
