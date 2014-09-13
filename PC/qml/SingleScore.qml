// A simple component showing a single score
import QtQuick 2.0

AnimatedElement {
	id: container

	// The rank of the score
	property int rank
	// The name of the player
	property string playerName
	// The score
	property real score
	// The portion of the width to use for the rank
	property real rankWidth: 0.1
	// The portion of the width to use for the score
	property real scoreWidth: 0.3

	Text {
		id: rankLabel
		x: 0
		y: 0
		width: container.width * container.rankWidth
		height: container.height
		horizontalAlignment: Text.AlignRight
		verticalAlignment: Text.AlignVCenter
		font { pointSize: 24; bold: true }
		text: container.rank + "."
		clip: true
	}

	Text {
		id: playerNameLabel
		x: rankLabel.x + rankLabel.width
		y: 0
		width: container.width * (1 - container.rankWidth - container.scoreWidth)
		height: container.height
		horizontalAlignment: Text.AlignLeft
		verticalAlignment: Text.AlignVCenter
		font { pointSize: 24; bold: true }
		text: " " + container.playerName
		clip: true
	}

	Text {
		id: scoreLabel
		x: playerNameLabel.x + playerNameLabel.width
		y: 0
		width: container.width * container.scoreWidth
		height: container.height
		horizontalAlignment: Text.AlignLeft
		verticalAlignment: Text.AlignVCenter
		font { pointSize: 24; bold: true }
		text: container.score
		clip: true
	}
}
