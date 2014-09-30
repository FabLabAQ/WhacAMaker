import QtQuick 2.0
import WhacAMaker 1.0

Rectangle {
	id: application
	color: "black" // "lightgray"
	width: 1024
	height: 768

	// The volume of sound effects
	property real volume: 1

	// The signal emitted when configuration parameters are saved
	signal configurationParametersSaved()
	// The signal emitted when a name is entered (to record an highscore)
	signal playerNameEntered(string playerName)
	// The signal emitted when joystick calibration starts
	signal joystickCalibrationStarted()
	// The signal emitted when joystick calibration ends
	signal joystickCalibrationEnded()
	// The signal sent when game starts
	signal gameStarted()
	// The signal sent when the game ends
	signal gameFinished()

	// The function returning the object that contains parameters (to be
	// restored by C++ code)
	function configurationParametersObject()
	{
		return configuration;
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
	// The function returning the joystick calibration object
	function joystickCalibrationObject()
	{
		return joystickCalibration;
	}
	// The function returning the joystick joystick pointer
	function joystickPointerObject()
	{
		return joystickPointer;
	}
	// The function returning the game panel object
	function gamePanelObject()
	{
		return game;
	}

	Item {
		id: internalItems

		anchors.fill:parent
// 		rotation: 90
// 		width: application.height
// 		height: application.width
// 		x: (height - width) / 2.0
// 		y: (width - height) / 2.0

		ButtonPanel {
			id: mainMenu
			visible: true
			buttonCaptions: ["Gioco", "Punteggi", "Impostazioni"]
			backButtonCaption: "Uscita"
			anchors.fill: parent

			onGoBack: { Qt.quit() }
		}

		ButtonPanel {
			id: gameModalityMenu
			visible: false
			backItem: mainMenu
			buttonCaptions: ["Classico", "Colore"]
			anchors.fill: parent

			onButtonClicked: {
				if (caption == "Classico") {
					game.gameModality = WhacAMaker.Classical;
				} else if (caption == "Colore") {
					game.gameModality = WhacAMaker.MatchColor;
				}
			}
		}

		ButtonPanel {
			id: gameLevelMenu
			visible: false
			backItem: gameModalityMenu
			buttonCaptions: ["Facile", "Medio", "Difficile"]
			anchors.fill: parent

			onButtonClicked: {
				if (caption == "Facile") {
					game.difficultyLevel = WhacAMaker.Easy;
				} else if (caption == "Medio") {
					game.difficultyLevel = WhacAMaker.Medium;
				} else if (caption == "Difficile") {
					game.difficultyLevel = WhacAMaker.Hard;
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
			buttonCaptions: ["Test", "Calibrazione Joystick", "Configurazione"]
			anchors.fill: parent

			onButtonClicked: {
				if (caption == "Test") {
					game.gameModality = WhacAMaker.Test;
				}
			}
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

		GamePanel {
			id: game
			visible: false
			anchors.fill: parent
			volume: application.volume

			// Propagating the gameStarted signal
			onGameStarted: {
				application.gameStarted();
			}

			onGameFinished: {
				visible = false;

				// Propagating the signal
				application.gameFinished()

				// Checking what to show
				if (newHighScore) {
					nameSelection.visible = true;
				} else {
					mainMenu.visible = true;
				}
			}
		}

		Configuration {
			id: configuration
			visible: false
			panelToShow: settingsMenu
			anchors.fill: parent

			onSave: application.configurationParametersSaved()
		}

		JoystickCalibration {
			id: joystickCalibration
			visible: false
			backItem: settingsMenu
			anchors.fill: parent

			onStart: application.joystickCalibrationStarted()
			onEnd: application.joystickCalibrationEnded()
		}

		NameSelection {
			id: nameSelection
			labelText: "Ottimo punteggio!"
			visible: false
			backItem: mainMenu
			anchors.fill: parent
			volume: application.volume

			onEnterPressed: application.playerNameEntered(t)
		}

		JoystickPointer {
			id: joystickPointer
		}
	}

	Component.onCompleted: {
		// Here we associate menus with buttons
		mainMenu.buttonItems = [gameLevelMenu, scoreLevelMenu, settingsMenu]
		gameModalityMenu.buttonItems = [gameLevelMenu, gameLevelMenu]
		gameLevelMenu.buttonItems = [game, game, game]
		scoreLevelMenu.buttonItems = [easyHighScores, mediumHighScores, hardHighScores]
		settingsMenu.buttonItems = [game, joystickCalibration, configuration]
	}
}
