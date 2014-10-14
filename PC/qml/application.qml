import QtQuick 2.3
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
	// The function returning the easy score object for classical modality
	function classicaleasyScoreObject()
	{
		return classicalEasyHighScores;
	}
	// The function returning the medium score object for classical modality
	function classicalmediumScoreObject()
	{
		return classicalMediumHighScores;
	}
	// The function returning the hard score object for classical modality
	function classicalhardScoreObject()
	{
		return classicalHardHighScores;
	}
	// The function returning the easy score object for match color modality
	function matchcoloreasyScoreObject()
	{
		return matchColorEasyHighScores;
	}
	// The function returning the medium score object for match color
	// modality
	function matchcolormediumScoreObject()
	{
		return matchColorMediumHighScores;
	}
	// The function returning the hard score object for match colot modality
	function matchcolorhardScoreObject()
	{
		return matchColorHardHighScores;
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
			id: scoreModalityMenu
			visible: false
			backItem: mainMenu
			buttonCaptions: ["Classico", "Colore"]
			anchors.fill: parent

			onButtonClicked: {
				if (caption == "Classico") {
					scoreLevelMenu.buttonItems = [classicalEasyHighScores, classicalMediumHighScores, classicalHardHighScores]
				} else if (caption == "Colore") {
					scoreLevelMenu.buttonItems = [matchColorEasyHighScores, matchColorMediumHighScores, matchColorHardHighScores]
				}
			}
		}

		ButtonPanel {
			id: scoreLevelMenu
			visible: false
			backItem: scoreModalityMenu
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
			id: classicalEasyHighScores
			visible: false
			backItem: scoreLevelMenu
			anchors.fill: parent
		}

		HighScores {
			id: classicalMediumHighScores
			visible: false
			backItem: scoreLevelMenu
			anchors.fill: parent
		}

		HighScores {
			id: classicalHardHighScores
			visible: false
			backItem: scoreLevelMenu
			anchors.fill: parent
		}

		HighScores {
			id: matchColorEasyHighScores
			visible: false
			backItem: scoreLevelMenu
			anchors.fill: parent
		}

		HighScores {
			id: matchColorMediumHighScores
			visible: false
			backItem: scoreLevelMenu
			anchors.fill: parent
		}

		HighScores {
			id: matchColorHardHighScores
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
					nameSelection.score = finalScore;
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
			labelText: "Ottimo punteggio! " + score + " punti"
			visible: false
			backItem: mainMenu
			anchors.fill: parent
			volume: application.volume
			property real score: 0

			onEnterPressed: application.playerNameEntered(t)
		}

		JoystickPointer {
			id: joystickPointer
		}
	}

	Component.onCompleted: {
		// Here we associate menus with buttons
		mainMenu.buttonItems = [gameModalityMenu, scoreLevelMenu, settingsMenu]
		gameModalityMenu.buttonItems = [gameLevelMenu, gameLevelMenu]
		gameLevelMenu.buttonItems = [game, game, game]
		scoreModalityMenu.buttonItems = [scoreLevelMenu, scoreLevelMenu]
		settingsMenu.buttonItems = [game, joystickCalibration, configuration]
	}
}
