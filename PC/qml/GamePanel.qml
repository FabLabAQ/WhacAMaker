// The panel for the game. The game area takes a square portion on the left/up
// side, the rest is used to show game information (difficulty level, score,
// time left...). A mouse click on the game area terminates the game earlier
import QtQuick 2.0
import WhackAMaker 1.0

AnimatedElementsPanel {
	id: container

	// The difficulty level
	property int difficultyLevel

	// Aliases for properties in GameInformation
	// The text with the current level
	property alias infoLevel: gameInformation.level
	// The current score
	property alias infoScore: gameInformation.score
	// The remaining ammunitions
	property alias infoAmmo: gameInformation.ammo
	// The remaining time
	property alias infoTime: gameInformation.time

	// The total game area size
	property real gameAreaSize: internalVars.moleCellSize * 3

	// The signal emitted when the game starts
	signal gameStarted()
	// The signal emitted when the game has finished. If newHighScore is
	// true we have a new highscore
	signal gameFinished(bool newHighScore)
	// The signal emitted when the game has to be terminated earlier (mouse
	// button click)
	signal terminateGame()

	// The function to close the game
	function endGame(newHighScore)
	{
		internalVars.newHighScore = newHighScore

		hideAll();
	}
	// The function to switch mole cells spots on of off. The status
	// parameter has the same format as the status used for Arduino, it is
	// and integer and each bit corresponds to a mole
	function changeMoleSpotStatus(status)
	{
		for (var i = 0; i < internalVars.moleCells.length; i++) {
			var state = (status >> i) & 1;
			if (state == 1) {
				internalVars.moleCells[i].state = "spotOn";
			} else {
				internalVars.moleCells[i].state = "";
			}
		}
	}

	// Sets which cell is pointed
	function setPointedMole(moleID)
	{
		for (var i = 0; i < internalVars.moleCells.length; i++) {
			if (i == moleID) {
				internalVars.moleCells[i].pointed = true;
			} else {
				internalVars.moleCells[i].pointed = false;
			}
		}
	}

	// Creates all moles cells
	function createCells()
	{
		// Deleting old cells
		for (button in internalVars.moleCells) {
			moleCells.destroy();
		}
		internalVars.moleCells = [];

		// Here we only create the cells, without placing them (we need a temporary array to trigger the update
		// of animatedElements)
		var tmpList = []
		for (var i = 0; i < 9; i++) {
			var component = Qt.createComponent("MoleCell.qml");
			var cell = component.createObject(container, {"name": ("Cell" + i)});

			if (cell == null) {
				console.log("Error creating button " + caption);
			}

			cell.index = i;
			cell.size = Qt.binding(function() { return internalVars.moleCellSize });
			cell.x = Qt.binding(function() { return internalVars.moleCellSize * (this.index % 3) });
			cell.yWhenVisible = Qt.binding(function() { return internalVars.moleCellSize * Math.floor(this.index / 3) });
			tmpList.push(cell);
		}

		internalVars.moleCells = tmpList;
	}

	// The mouse area. A click on any point in the game terminates the game
	// earlier
	MouseArea {
		anchors.fill: parent
		onClicked: container.terminateGame()
	}

	// The item with information about the game
	GameInformation {
		id: gameInformation

		width: (container.width < container.height) ? container.width : (container.width - container.height)
		height: (container.height < container.width) ? container.height : (container.height - container.width)
		x: (container.width < container.height) ? 0 : container.height
		yWhenVisible: (container.height < container.width) ? 0 : container.width
	}

	// An object with internal variables
	QtObject {
		id: internalVars

		// The list of mole cells
		property var moleCells: []
		// The size od each mole cell
		property var moleCellSize: (container.width < container.height) ? (container.width / 3) : (container.height / 3)
		// Whether the player scored a new highscore
		property bool newHighScore: false
	}

	// The animated elements
	animatedElements: [gameInformation].concat(internalVars.moleCells)

	// Called when all elements have appeared
	onAllAppeared: {
		// Signalling game start
		gameStarted();
	}

	// Called when all elements have disappeared
	onAllDisappeared: {
		visible = false;

		// Also emitting the signal for game finished
		gameFinished(internalVars.newHighScore);
	}

	Component.onCompleted: {
		createCells();
	}
}
