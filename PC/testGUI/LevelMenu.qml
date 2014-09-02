import QtQuick 2.0

Rectangle {
	id: levelMenu
	width: 320
	height: 480
	color: "lightgray"

	signal easySelected
	signal mediumSelected
	signal hardSelected
	signal goBack

	Button {
		id: easyButton
		caption: "Facile"
		x: 10
		y: 10
		width: 300
		height: 50
		onClicked: levelMenu.easySelected()
	}

	Button {
		id: mediumButton
		caption: "Medio"
		x: 10
		y: 70
		width: 300
		height: 50
		onClicked: levelMenu.mediumSelected()
	}

	Button {
		id: hardButton
		caption: "Difficile"
		x: 10
		y: 130
		width: 300
		height: 50
		onClicked: levelMenu.hardSelected()
	}

	Button {
		id: backButton
		caption: "Indietro"
		x: 10
		y: 190
		width: 300
		height: 50
		onClicked: levelMenu.goBack()
	}
}
