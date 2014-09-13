import QtQuick 2.0
import TiroAlMostro 1.0

Rectangle {
	id: application
	color: "lightgray"
	width: 640
	height: 480

	// The signal emitted when configuration parameters are saved. Obj is
	// the object that contains the parameters
	signal configurationParametersSaved(var obj)
	// The signal emitted when a name is entered (to record an highscore)
	signal playerNameEntered(string playerName)

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

		onButtonClicked: { console.log("Pressed button " + caption) }
	}

	HighScores {
		id: easyHighScores
		visible: false
		backItem: scoreLevelMenu
		playersNames: ["Pippo", "Pluto", "Paperino"]
		playersScores: [50, 40, 10]
		anchors.fill: parent
	}

	HighScores {
		id: mediumHighScores
		visible: false
		backItem: scoreLevelMenu
		playersNames: ["Paperino", "Pluto", "Pippo"]
		playersScores: [40, 20, 5]
		anchors.fill: parent
	}

	HighScores {
		id: hardHighScores
		visible: false
		backItem: scoreLevelMenu
		playersNames: ["Pluto", "Paperino", "Pippo"]
		playersScores: [19, 12, 2]
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
