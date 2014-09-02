import QtQuick 2.0

Rectangle {
	id: application
	color: "black"
	width: 320
	height: 480

	states: [
		State {
			name: "gameLevelMenu"
			PropertyChanges {
				target: mainMenu
				visible: false
			}
			PropertyChanges {
				target: levelMenu
				visible: true
			}
			PropertyChanges {
				target: settingsMenu
				visible: false
			}
			PropertyChanges {
				target: game
				visible: false
			}
		},
		State {
			name: "settingsMenu"
			PropertyChanges {
				target: mainMenu
				visible: false
			}
			PropertyChanges {
				target: levelMenu
				visible: false
			}
			PropertyChanges {
				target: settingsMenu
				visible: true
			}
			PropertyChanges {
				target: game
				visible: false
			}
		},
		State {
			name: "game"
			PropertyChanges {
				target: mainMenu
				visible: false
			}
			PropertyChanges {
				target: levelMenu
				visible: false
			}
			PropertyChanges {
				target: settingsMenu
				visible: false
			}
			PropertyChanges {
				target: game
				visible: true
			}
		}
	]

	MainMenu {
		id: mainMenu
		visible: true

		onStartGame: { application.state = "gameLevelMenu" }
		onShowScore: { application.state = "" }
		onShowSettings: { application.state = "settingsMenu" }
		onExit: { Qt.quit() }
	}

	LevelMenu {
		id: levelMenu
		visible: false

		onEasySelected: { application.state = "game" }
		onMediumSelected: { application.state = "game" }
		onHardSelected: { application.state = "game" }
		onGoBack: { application.state = "" }
	}

	SettingsMenu {
		id: settingsMenu
		visible: false

		onConfigure: {}
		onGoBack: { application.state = "" }
	}

	Game {
		id: game
		visible: false

		onGoBack: { application.state = "" }
	}
}
