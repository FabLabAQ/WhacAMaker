// The panel showing high scores
import QtQuick 2.0

AnimatedElementsPanel {
	id: container
	// The panel to show when back is clicked. If this is null only the
	// goBack signal is emitted
	property var backItem: null
	// The list of players. Each element is a string with the name of the
	// player
	property var playersNames: []
	// The list of scores for players in the playersNames list. Each element
	// is a real value. If this list has less elements than playersNames the
	// score for players from playersScores.length on are set to 0
	property var playersScores: []
	// The list of SingleScore objects. This is created at startup depending
	// on the list of players names
	property var singleScores: []

	// The signal emitted when the back button is clicked
	signal goBack()

	// Generare i SingleScore automaticamente!!!

	SingleScore {
		id: prova
		x: 10
		yWhenVisible: 10
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
