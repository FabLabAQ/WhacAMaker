// The panel showing high scores
import QtQuick 2.0

AnimatedElementsPanel {
	id: container
	// The panel to show when back is clicked. If this is null only the
	// goBack signal is raised
	property var panelToShow: null

	// AGGIUNGERE BACK ITEM, BACK LABEL E PULSANTE

	SingleScore {
		id: prova
		x: 10
		yWhenVisible: 10
		yWhenInvisible: -height
		width: 400
		height: 100
		rank: 3
		playerName: "Tomassino"
		score: 130.0
	}

	// The list of elements to animate
	animatedElements: [prova]
}
