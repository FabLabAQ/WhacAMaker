import QtQuick 2.0

Rectangle {
	id: settingsMenu
	width: 320
	height: 480
	color: "lightgray"

	signal configure
	signal goBack

	Button {
		id: easyButton
		caption: "Facile"
		x: 10
		y: 10
		width: 300
		height: 50
		onClicked: settingsMenu.configure()
	}

	Button {
		id: backButton
		caption: "Indietro"
		x: 10
		y: 190
		width: 300
		height: 50
		onClicked: settingsMenu.goBack()
	}
}
