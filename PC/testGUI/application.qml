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
			PropertyChanges {
				target: testPanel
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
			PropertyChanges {
				target: testPanel
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
			PropertyChanges {
				target: testPanel
				visible: false
			}
		},
		State {
			name: "testPanel"
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
				visible: false
			}
			PropertyChanges {
				target: testPanel
				visible: true
			}
		}
	]

	ButtonPanel {
		id: mainMenu
		visible: true
		buttonCaptions: ["Gioco", "Punteggi", "Impostazioni"]
		backButtonCaption: "Uscita"
		anchors.fill: parent

		onGoBack: { Qt.quit() }
		onButtonClicked: {
			if (caption == "Gioco") {
				application.state = "gameLevelMenu";
			} else if (caption == "Punteggi") {
				application.state = "testPanel";
			} else if (caption == "Impostazioni") {
				application.state = "settingsMenu";
			}
		}
	}

	ButtonPanel {
		id: levelMenu
		visible: false
		buttonCaptions: ["Facile", "Medio", "Difficile"]
		anchors.fill: parent

		onGoBack: { application.state = "" }
		onButtonClicked: {
			if (caption == "Facile") {
				application.state = "game";
			} else if (caption == "Medio") {
				application.state = "game";
			} else if (caption == "Difficile") {
				application.state = "game";
			}
		}
	}

	ButtonPanel {
		id: settingsMenu
		visible: false
		buttonCaptions: ["Facile"]
		anchors.fill: parent

		onGoBack: { application.state = "" }
		onButtonClicked: { console.log("Pressed button " + caption) }
	}

	Game {
		id: game
		visible: false

		onGoBack: { application.state = "" }
	}

	ButtonPanel {
		id: testPanel
		visible: false
		buttonCaptions: ["Primo", "Secondo", "Contorno"]
		anchors.fill: parent

		onGoBack: { application.state = "" }
		onButtonClicked: { console.log("Pressed button " + caption) }
	}
}
