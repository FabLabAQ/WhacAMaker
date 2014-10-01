// The item with information about the game (level, score, time left...)
import QtQuick 2.3
import QtQuick.Layouts 1.1

AnimatedElement {
	id: container

	// The list of fields with information to show. This is a list of
	// strings, which are used as captions (if captions are shown)
	property var fields: []
	// If true field captions are shown, otherwise they are hidden
	property bool showCaptions: true
	// The font size
	property real fontPointSize: 32 // 72 // 24
	// The font type
	property string fontFamily: "Digital-7 Mono"
	// The text color
	property color textColor: "green"

	// The function to set the value to display for the i-th field. The
	// field with id 0 is always the game modality and level, other start
	// from 1
	function setFieldValue(i, value)
	{
		// Ignoring invalid indexes
		if ((i < 0) || (i >= information.count)) {
			return;
		}

		information.itemAt(i).value = value;
	}

	// The layout with all information
	ColumnLayout {
		spacing: 0
		anchors.fill: parent
		anchors.margins: container.width / 10.0

		// The repeater creates all labels and values
		Repeater {
			id: information
			model: ["Modalità"].concat(container.fields)

			// Inside this column positioner we put the text with
			// the caption and the value
			Column {
				// An alias for the value to show
				property alias value: valueText.text

				// Caption
				Text {
					id: captionText

					text: modelData
					font { pointSize: container.fontPointSize; family: container.fontFamily }
					color: container.textColor
					visible: container.showCaptions
				}
				// Value
				Text {
					id: valueText

					font { pointSize: container.fontPointSize; family: container.fontFamily }
					color: container.textColor
				}
			}
		}
	}
}
