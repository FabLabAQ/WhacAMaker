import QtQuick 2.0
import TiroAlMostro 1.0

Rectangle {
	id: application
	color: "lightgray"
	width: 640
	height: 480

	// The signal emitted when configuration parameters are saved
	signal configurationParametersSaved()
	// The signal emitted when a name is entered (to record an highscore)
	signal playerNameEntered(string playerName)

	// The function returning the object that contains parameters (to be
	// restored by C++ code)
	function configurationParametersObject()
	{
		return configurationMenu;
	}
	// The function returning the game object
	function gameObject()
	{
		return game;
	}
	// The function returning the easy score object
	function easyScoreObject()
	{
		return easyHighScores;
	}
	// The function returning the medium score object
	function mediumScoreObject()
	{
		return mediumHighScores;
	}
	// The function returning the hard score object
	function hardScoreObject()
	{
		return hardHighScores;
	}

	ButtonPanel {
		id: mainMenu
		visible: true
		buttonCaptions: ["Gioco", "Punteggi", "Impostazioni"]
		backButtonCaption: "Uscita"
		anchors.fill: parent

		onGoBack: { Qt.quit() }
	}

	ButtonPanel {
		id: gameLevelMenu
		visible: false
		backItem: mainMenu
		buttonCaptions: ["Facile", "Medio", "Difficile"]
		anchors.fill: parent

		onButtonClicked: {
			if (caption == "Facile") {
				game.difficultyLevel = GameItem.Easy;
			} else if (caption == "Medio") {
				game.difficultyLevel = GameItem.Medium;
			} else if (caption == "Difficile") {
				game.difficultyLevel = GameItem.Hard;
			}
		}
	}

	ButtonPanel {
		id: scoreLevelMenu
		visible: false
		backItem: mainMenu
		buttonCaptions: ["Facile", "Medio", "Difficile"]
		anchors.fill: parent
	}

	ButtonPanel {
		id: settingsMenu
		visible: false
		backItem: mainMenu
		buttonCaptions: ["Calibrazione", "Configurazione"]
		anchors.fill: parent
	}

	HighScores {
		id: easyHighScores
		visible: false
		backItem: scoreLevelMenu
		anchors.fill: parent
	}

	HighScores {
		id: mediumHighScores
		visible: false
		backItem: scoreLevelMenu
		anchors.fill: parent
	}

	HighScores {
		id: hardHighScores
		visible: false
		backItem: scoreLevelMenu
		anchors.fill: parent
	}

	GameItem {
		id: game
		visible: false
		anchors.fill: parent

		onGameFinished: {
			visible = false;

			if (newHighScore) {
				nameSelection.visible = true;
			} else {
				mainMenu.visible = true;
			}
		}
	}

	Configuration {
		id: configurationMenu
		visible: false
		panelToShow: settingsMenu
		anchors.fill: parent

		onSave: configurationParametersSaved(configurationMenu)
	}

	NameSelection {
		id: nameSelection
		labelText: "Ottimo punteggio!"
		visible: false
		backItem: mainMenu
		anchors.fill: parent

		onEnterPressed: playerNameEntered(t)
	}

	Component.onCompleted: {
		// Here we associate menus with buttons
		mainMenu.buttonItems = [gameLevelMenu, scoreLevelMenu, settingsMenu]
		gameLevelMenu.buttonItems = [game, game, game]
		scoreLevelMenu.buttonItems = [easyHighScores, mediumHighScores, hardHighScores]
		settingsMenu.buttonItems = [null, configurationMenu]
	}
}
