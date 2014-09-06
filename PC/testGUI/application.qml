import QtQuick 2.0

Rectangle {
	id: application
	color: "black"
	width: 640
	height: 480

	ButtonPanel {
		id: mainMenu
		visible: true
		buttonCaptions: ["Gioco", "Punteggi", "Impostazioni"]
		backButtonCaption: "Uscita"
		anchors.fill: parent

		onGoBack: { Qt.quit() }
	}

	ButtonPanel {
		id: levelMenu
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

	Game {
		id: game
		visible: false

		onGoBack: { visible = false; mainMenu.visible = true; }
	}

	ButtonPanel {
		id: testPanel
		visible: false
		backItem: mainMenu
		buttonCaptions: ["Primo", "Secondo", "Contorno"]
		anchors.fill: parent

		onButtonClicked: { console.log("Pressed button " + caption) }
	}

	Component.onCompleted: {
		// Here we associate menus with buttons
		mainMenu.buttonItems = [levelMenu, testPanel, settingsMenu]
		levelMenu.buttonItems = [game, game, game]
	}
}
