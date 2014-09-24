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
	// The signal emitted when joystick calibration starts
	signal joystickCalibrationStarted()
	// The signal emitted when joystick calibration is cancelled by the user
	signal joystickCalibrationInterrupted()
	// The signal sent when game starts
	signal gameStarted()

	// The function returning the object that contains parameters (to be
	// restored by C++ code)
	function configurationParametersObject()
	{
		return configuration;
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
	// The function returning the joystick calibration object
	function joystickCalibrationObject()
	{
		return joystickCalibration;
	}
	// The function to end the joystick calibration procedure
	function endJoystickCalibration()
	{
		joystickCalibration.endCalibration();
	}
	// The function returning the joystick joystick pointer
	function joystickPointerObject()
	{
		return joystickPointer;
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
		buttonCaptions: ["Calibrazione Joystick", "Configurazione"]
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

		onVisibleChanged: {
			if (visible) {
				gameStarted();
			}
		}

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

		onCalibrationStarted: application.joystickCalibrationStarted()
		onGoBack: application.joystickCalibrationInterrupted()
	}

	NameSelection {
		id: nameSelection
		labelText: "Ottimo punteggio!"
		visible: false
		backItem: mainMenu
		anchors.fill: parent

		onEnterPressed: application.playerNameEntered(t)
	}

	JoystickPointer {
		id: joystickPointer
	}

	Component.onCompleted: {
		// Here we associate menus with buttons
		mainMenu.buttonItems = [gameLevelMenu, scoreLevelMenu, settingsMenu]
		gameLevelMenu.buttonItems = [game, game, game]
		scoreLevelMenu.buttonItems = [easyHighScores, mediumHighScores, hardHighScores]
		settingsMenu.buttonItems = [joystickCalibration, configuration]
	}
}
