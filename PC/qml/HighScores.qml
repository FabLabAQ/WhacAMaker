// The panel showing high scores
import QtQuick 2.0

AnimatedElementsPanelWithItems {
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

	// The signal emitted when the back button is clicked
	signal goBack()

	// The items vector is filled by the slots for changes on playersNames
	// and playersScores, the buttons vector only contains the back button
	buttons: [backButton]

	function createHighScoreItems()
	{
		// Deleting old scores
		for (singleScore in items) {
			singleScore.destroy()
		}
		items = []

		// Here we create all single scores
		for (var i = 0; i < playersNames.length; i++) {
			var component = Qt.createComponent("SingleScore.qml");

			var score = 0
			if (playersScores.length > i) {
				score = playersScores[i];
			}
			var singleScore = component.createObject(container, {"rank": (i + 1), "playerName": playersNames[i], "score": score});

			if (singleScore == null) {
				console.log("Error creating singleScore for " + playersNames[i]);
			}

			// Adding to to the list of items
			items.push(singleScore);
		}
	}

	// Finally adding the back button
	Button {
		id: backButton
		caption: "Indietro"

		onClicked: {
			goBack();
			if (backItem != null) {
				hideAll();
			}
		}
	}

	// The function called when all elements have disappeared
	onAllDisappeared: {
		visible = false;
		if (backItem != null) {
			backItem.visible = true;
		}
	}

	// When the list of players or scorechange, the SingleScore are created
	// again. We need to check whether the playersScores is an array because
	// when the application starts, we could have playersNames initialized
	// and playersScores still undefined (or viceversa) and we would get
	// warnings. This way we are sure that both have been initialized
	onPlayersNamesChanged: {
		if (Array.isArray(playersScores)) {
			createHighScoreItems();
		}
	}
	onPlayersScoresChanged: {
		if (Array.isArray(playersNames)) {
			createHighScoreItems();
		}
	}
}
