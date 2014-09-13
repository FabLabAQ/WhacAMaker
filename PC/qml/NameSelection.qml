// A panel that allows to select a text with a on-screen keyboard
import QtQuick 2.0

AnimatedElementsPanel {
	id: container

	// The panel to show when enter is pressed. If this is null, only the
	// enterPressed signal is emitted
	property var backItem: null
	// The maximum allowed number of characters
	property int maxCharacters: 10

	// The signal emitted when the enter keyboard is pressed. t is the text
	// that has been entered
	signal enterPressed(string t)

	// The label with text
	AnimatedLabel {
		id: label
		x: (container.width - width) / 2
		yWhenVisible: (container.height - keyboard.height) / 3
		width: container.width / 2
		height: (container.height - keyboard.height) / 3
		clip: true
	}

	// The keyboard to enter text
	Keyboard {
		id: keyboard
		x: 0
		yWhenVisible: container.height - keyboard.height
		width: container.width
		height: preferredHeight

		onBackspace: {
			label.text = label.text.substr(0, label.text.length - 1);
		}

		onEnter: {
			enterPressed(label.text);

			if (backItem != null) {
				container.hideAll();
			}
		}

		onKeyPressed: {
			if (label.text.length < maxCharacters) {
				label.text += c;
			}
		}
	}

	// The animated elements
	animatedElements: [label, keyboard]

	// Called when all buttons have disappeared
	onAllDisappeared: {
		visible = false;
		if (backItem != null) {
			backItem.visible = true;
		}
	}

	// We need to reimplement this to clear the label text
	onVisibleChanged: {
		label.text = "";

		if (visible) {
			showAll();
		}
	}
}
