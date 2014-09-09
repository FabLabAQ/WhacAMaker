// The panel showing high scores
import QtQuick 2.0

AnimatedElementsPanel {
	id: container
	// The panel to show when back is clicked. If this is null only the
	// goBack signal is raised
	property var backItem: null

	// The signal emitted when the back button is clicked
	signal goBack()

	// AGGIUNGERE BACK ITEM, BACK LABEL E PULSANTE. Inoltre mettere vettori di player e score e generare i SingleScore automaticamente

	SingleScore {
		id: prova
		x: 10
		yWhenVisible: 10
		yWhenInvisible: -height
		width: 400
		height: 40
		rank: 3
		playerName: "Tomassino"
		score: 130.0
	}

	// Finally adding the back button
	Button {
		id: backButton
		caption: "Indietro"
		x: 10
		yWhenVisible: 60
		width: 400
		height: 40

		onClicked: {
			goBack();
			if (backItem != null) {
				hideAll();
			}
		}
	}

	// The list of elements to animate
	animatedElements: [prova, backButton]

	// The function called when all elements have disappeared
	onAllDisappeared: {
		visible = false;
		if (backItem != null) {
			backItem.visible = true;
		}
	}
}
