// The panel showing high scores
import QtQuick 2.0

Item {
	id: container
	// The panel to show when back is clicked. If this is null only the
	// goBack signal is raised
	property var panelToShow: null

	FARE COMPONENTE GENERICO CHE CONTIENE ANIMATEDELEMENTS
// 	// The width of input fields relative to the container width
// 	property real inputFieldsWidth: 0.9
// 	// The height of input fields. If inputFieldsRelativeHeight is true this
// 	// is relative to the component height, otherwise this is the actual
// 	// height of input fields
// 	property real inputFieldsHeight: 0.1
// 	// If true inputFieldsHeight is relative to the component height,
// 	// otherwise inputFieldsHeight is the actual height of input fields
// 	property bool inputFieldsRelativeHeight: true
// 	// The spacing between input fields. This is relative to the input
// 	// fields height
// 	property real inputFieldsSpacing: 0.3
// 	// The proportion of the label with respect to the input field
// 	property real labelInputProportion: 0.5
// 	// The space between the text area and the label
// 	property real labelInputSpacing: 10
//
// 	// The width of buttons. If buttonRelativeWidth is true this is relative
// 	// to the component width, otherwise this is the actual width of
// 	// buttons.
// 	property real buttonsWidth: 0.3
// 	// The height of buttons relative to the container height.
// 	property real buttonsHeight: 0.1
// 	// If true buttonHeight is relative to the component height, otherwise
// 	// buttonHeight is the actual height of buttons
// 	property bool buttonsRelativeWidth: true
// 	// The spacing between buttons. This is relative to the button width
// 	property real buttonsSpacing: 0.3
//
// 	// The signal raised when the save button is clicked
// 	signal save()
// 	// The signal raised when the back button is clicked
// 	signal goBack()
//
// 	// Here we have all values computed automatically from properties above
// 	QtObject {
// 		id: internalValues
//
// 		// The x position of input fields
// 		property real inputFieldsX: ((1 - container.inputFieldsWidth) * container.width) / 2
// 		// The y position of the first input field
// 		property real inputFieldFirstY: (container.height - inputFieldsHeight * 4 - inputFieldsSpacing * 4 - buttonsHeight) / 2
// 		// The actual width of input fields
// 		property real inputFieldsWidth: container.inputFieldsWidth * container.width
// 		// The actual height of input fields
// 		property real inputFieldsHeight: (container.inputFieldsRelativeHeight == true) ? (container.inputFieldsHeight * container.height) : container.inputFieldsHeight
// 		// The actual vertical spacing of input fields
// 		property real inputFieldsSpacing: inputFieldsHeight * container.inputFieldsSpacing
// 		// The x position of buttons
// 		property real buttonsFirstX: (container.width - 2 * buttonsWidth - buttonsSpacing) / 2
// 		// The y position of buttons
// 		property real buttonsY: inputFieldFirstY + 4 * inputFieldsHeight + 4 * inputFieldsSpacing
// 		// The actual width of buttons
// 		property real buttonsWidth: (container.buttonsRelativeWidth == true) ? (container.buttonsWidth * container.width) : container.buttonsWidth
// 		// The actual height of buttons
// 		property real buttonsHeight: container.buttonsHeight * container.height
// 		// The actual spacing between buttons
// 		property real buttonsSpacing: container.buttonsSpacing * buttonsWidth
// 	}
//
// 	// Adding input fields: usb port...
// 	InputField {
// 		id: serialPort
// 		label: "Porta seriale Gioco:"
// 		x: internalValues.inputFieldsX
// 		yWhenVisible: internalValues.inputFieldFirstY
// 		yWhenInvisible: -height
// 		width: internalValues.inputFieldsWidth
// 		height: internalValues.inputFieldsHeight
// 		labelInputProportion: container.labelInputProportion
// 		spacing: container.labelInputSpacing
//
// 		onDisappeared: internalDisappeared()
// 	}
//
// 	// ... distance from screen...
// 	InputField {
// 		id: screenDistance
// 		label: "Distanza dallo schermo:"
// 		x: internalValues.inputFieldsX
// 		yWhenVisible: serialPort.yWhenVisible + serialPort.height + internalValues.inputFieldsSpacing
// 		yWhenInvisible: -height
// 		width: internalValues.inputFieldsWidth
// 		height: internalValues.inputFieldsHeight
// 		labelInputProportion: container.labelInputProportion
// 		spacing: container.labelInputSpacing
// 		validator: DoubleValidator { bottom: 0 }
//
// 		onDisappeared: internalDisappeared()
// 	}
//
// 	// ... vertical distance from screen center...
// 	InputField {
// 		id: verticalScreenCenterDistance
// 		label: "Distanza verticale dal centro dello schermo:"
// 		x: internalValues.inputFieldsX
// 		yWhenVisible: screenDistance.yWhenVisible + screenDistance.height + internalValues.inputFieldsSpacing
// 		yWhenInvisible: -height
// 		width: internalValues.inputFieldsWidth
// 		height: internalValues.inputFieldsHeight
// 		labelInputProportion: container.labelInputProportion
// 		spacing: container.labelInputSpacing
// 		validator: DoubleValidator {}
//
// 		onDisappeared: internalDisappeared()
// 	}
//
// 	// ... and horizontal distance from screen center.
// 	InputField {
// 		id: horizontalScreenCenterDistance
// 		label: "Distanza orizzontale dal centro dello schermo:"
// 		x: internalValues.inputFieldsX
// 		yWhenVisible: verticalScreenCenterDistance.yWhenVisible + verticalScreenCenterDistance.height + internalValues.inputFieldsSpacing
// 		yWhenInvisible: -height
// 		width: internalValues.inputFieldsWidth
// 		height: internalValues.inputFieldsHeight
// 		labelInputProportion: container.labelInputProportion
// 		spacing: container.labelInputSpacing
// 		validator: DoubleValidator {}
//
// 		onDisappeared: internalDisappeared()
// 	}
//
// 	// Now adding the buttons to save...
// 	Button {
// 		id: saveButton
// 		caption: "Salva"
// 		x: internalValues.buttonsFirstX
// 		yWhenVisible: internalValues.buttonsY
// 		yWhenInvisible: -height
// 		width: internalValues.buttonsWidth
// 		height: internalValues.buttonsHeight
//
// 		onDisappeared: internalDisappeared()
// 		onClicked: {
// 			save();
// 			if (panelToShow != null) {
// 				hideAll();
// 			}
// 		}
// 	}
//
// 	// ... and to go back.
// 	Button {
// 		id: backButton
// 		caption: "Indietro"
// 		x: saveButton.x + saveButton.width + internalValues.buttonsSpacing
// 		yWhenVisible: internalValues.buttonsY
// 		yWhenInvisible: -height
// 		width: internalValues.buttonsWidth
// 		height: internalValues.buttonsHeight
//
// 		onDisappeared: internalDisappeared()
// 		onClicked: {
// 			goBack();
// 			if (panelToShow != null) {
// 				hideAll();
// 			}
// 		}
// 	}
//
// 	// An internal function called when controls disappear that hides this
// 	// panel and shows panelToShow if all controls have disappeared
// 	function internalDisappeared()
// 	{
// 		var anyVisible = serialPort.visible || screenDistance.visible || verticalScreenCenterDistance.visible || horizontalScreenCenterDistance.visible || saveButton.visible || backButton.visible;
//
// 		if (anyVisible == false) {
// 			visible = false;
// 			if (panelToShow == null) {
//
// 			} else {
// 				panelToShow.visible = true;
// 			}
// 		}
// 	}
//
// 	// A function to show all controls
// 	function showAll()
// 	{
// 		serialPort.state = "appearing";
// 		screenDistance.state = "appearing";
// 		verticalScreenCenterDistance.state = "appearing";
// 		horizontalScreenCenterDistance.state = "appearing";
// 		saveButton.state = "appearing";
// 		backButton.state = "appearing";
// 	}
//
// 	// A function to hide all controls
// 	function hideAll()
// 	{
// 		serialPort.state = "disappearing";
// 		screenDistance.state = "disappearing";
// 		verticalScreenCenterDistance.state = "disappearing";
// 		horizontalScreenCenterDistance.state = "disappearing";
// 		saveButton.state = "disappearing";
// 		backButton.state = "disappearing";
// 	}
//
// 	Component.onCompleted: {
// 		if (visible) {
// 			showAll()
// 		}
// 	}
//
// 	onVisibleChanged: {
// 		if (visible) {
// 			showAll();
// 		}
// 	}
}
