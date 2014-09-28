// The item with information about the game (level, score, time left...)
import QtQuick 2.0

AnimatedElement {
	id: container

	// The text with the current level
	property alias level: levelText.text
	// The current score
	property alias score: scoreText.text
	// The remaining ammunitions
	property alias ammo: ammoText.text
	// The remaining time
	property alias time: timeText.text
	// The font size
	property real fontPointSize: 72 // 24
	// The font type
	property string fontFamily: "Digital-7 Mono"
	// The text color
	property color textColor: "green"

	Text {
		id: levelLabel
		//text: "Livello"
		x: internalVars.textXPos
		y: internalVars.firstLineYPosInArea
		width: container.width
		height: internalVars.textHeight
		font { pointSize: container.fontPointSize; family: container.fontFamily }
		color: container.textColor
	}

	Text {
		id: levelText
		x: internalVars.textXPos
		y: levelLabel.y + levelLabel.height
		width: container.width
		height: internalVars.textHeight
		font { pointSize: container.fontPointSize; family: container.fontFamily }
		color: container.textColor
	}

	Text {
		id: scoreLabel
		//text: "Punteggio"
		x: internalVars.textXPos
		y: internalVars.textAreaHeight + internalVars.firstLineYPosInArea
		width: container.width
		height: internalVars.textHeight
		font { pointSize: container.fontPointSize; family: container.fontFamily }
		color: container.textColor
	}

	Text {
		id: scoreText
		x: internalVars.textXPos
		y: scoreLabel.y + scoreLabel.height
		width: container.width
		height: internalVars.textHeight
		font { pointSize: container.fontPointSize; family: container.fontFamily }
		color: container.textColor
	}

	Text {
		id: ammoLabel
		//text: "Colpi rimasti"
		x: internalVars.textXPos
		y: 2 * internalVars.textAreaHeight + internalVars.firstLineYPosInArea
		width: container.width
		height: internalVars.textHeight
		font { pointSize: container.fontPointSize; family: container.fontFamily }
		color: container.textColor
	}

	Text {
		id: ammoText
		x: internalVars.textXPos
		y: ammoLabel.y + ammoLabel.height
		width: container.width
		height: internalVars.textHeight
		font { pointSize: container.fontPointSize; family: container.fontFamily }
		color: container.textColor
	}

	Text {
		id: timeLabel
		//text: "Tempo rimasto"
		x: internalVars.textXPos
		y: 3 * internalVars.textAreaHeight + internalVars.firstLineYPosInArea
		width: container.width
		height: internalVars.textHeight
		font { pointSize: container.fontPointSize; family: container.fontFamily }
		color: container.textColor
	}

	Text {
		id: timeText
		x: internalVars.textXPos
		y: timeLabel.y + timeLabel.height
		width: container.width
		height: internalVars.textHeight
		font { pointSize: container.fontPointSize; family: container.fontFamily }
		color: container.textColor
	}

	// An object with internal variables
	QtObject {
		id: internalVars

		// The height of each text area
		property real textAreaHeight: container.height / 4.0;
		// The x position of text
		property real textXPos: container.width / 10.0;
		// The y position of the first line of text in the text area
		property real firstLineYPosInArea: textAreaHeight / 6.0;
		// The height of text
		property real textHeight: textAreaHeight / 3.0;
	}
}
