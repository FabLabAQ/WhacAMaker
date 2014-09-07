import QtQuick 2.0

Rectangle {
	id: application
	color: "lightgray"
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

	ButtonPanel {
		id: testPanel
		visible: false
		backItem: mainMenu
		buttonCaptions: ["Primo", "Secondo", "Contorno"]
		anchors.fill: parent

		onButtonClicked: { console.log("Pressed button " + caption) }
	}

	Game {
		id: game
		visible: false
		anchors.fill: parent

		onGoBack: { visible = false; mainMenu.visible = true; }
	}

	Configuration {
		id: configurationMenu
		visible: false
		panelToShow: settingsMenu
		anchors.fill: parent
	}

	Component.onCompleted: {
		// Here we associate menus with buttons
		mainMenu.buttonItems = [levelMenu, testPanel, settingsMenu]
		levelMenu.buttonItems = [game, game, game]
		settingsMenu.buttonItems = [null, configurationMenu]
	}
}
