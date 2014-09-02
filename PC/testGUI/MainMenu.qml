import QtQuick 2.0

Rectangle {
	id: mainMenu
	width: parent.width
	height: parent.height
	color: "lightgray"

	signal startGame
	signal showScore
	signal showSettings
	signal exit

	Button {
		id: gameButton
		caption: "Gioco"
		x: 10
		y: 10
		width: 300
		height: 50
		onClicked: mainMenu.startGame()
	}

	Button {
		id: scoreButton
		caption: "Punteggi"
		x: 10
		y: 70
		width: 300
		height: 50
		onClicked: mainMenu.showScore()
	}

	Button {
		id: settingsButton
		caption: "Impostazioni"
		x: 10
		y: 130
		width: 300
		height: 50
		onClicked: mainMenu.showSettings()
	}

	Button {
		id: exitButton
		caption: "Exit"
		x: 10
		y: 190
		width: 300
		height: 50
		onClicked: mainMenu.exit()
	}
}
