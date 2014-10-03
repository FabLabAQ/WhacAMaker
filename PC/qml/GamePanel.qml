// The panel for the game. The game area takes a square portion on the left/up
// side, the rest is used to show game information (difficulty level, score,
// time left...). A mouse click on the game area terminates the game earlier
import QtQuick 2.3
import WhacAMaker 1.0
import QtMultimedia 5.0

AnimatedElementsPanel {
	id: container

	// The game modality
	property int gameModality
	// The difficulty level
	property int difficultyLevel

	// Aliases for properties in GameInformation
	property alias informationFields: gameInformation.fields
	// The volume of sound effects
	property real volume: 1.0

	// The total game area size
	property real gameAreaSize: internalVars.moleCellSize * 3
	// The final score of the player
	property real finalScore: 0

	// The signal emitted when the game starts
	signal gameStarted()
	// The signal emitted when the game has finished. If newHighScore is
	// true we have a new highscore
	signal gameFinished(bool newHighScore)
	// The signal emitted when the game has to be terminated earlier (mouse
	// button click)
	signal terminateGame()

	// The function to set the value to display for the i-th field. The
	// field with id 0 is always the game modality and level, other start
	// from 1
	function setInformationFieldValue(i, value)
	{
		// Simply forwarding call to the GameInformation function
		gameInformation.setFieldValue(i, value);
	}

	// The function to close the game
	function endGame(newHighScore)
	{
		internalVars.newHighScore = newHighScore

		hideAll();
	}

	// The function to switch mole cells spots on or off. The status
	// parameter has the same format as the status used for Arduino, it is
	// and integer and each bit corresponds to a mole
	function changeMoleSpotStatus(status)
	{
		for (var i = 0; i < internalVars.moleCells.length; i++) {
			var state = (status >> i) & 1;
			if (state == 1) {
				internalVars.moleCells[i].spotOn = true;
			} else {
				internalVars.moleCells[i].spotOn = false;
			}
		}
	}

	// The function that changes the color of the spot of all moles. This
	// doesn't change the visible property of the spot
	function changeAllMolesSpotColor(color)
	{
		for (var i = 0; i < internalVars.moleCells.length; i++) {
			internalVars.moleCells[i].spotColor = color;
		}
	}

	// The function that changes the color of the spot of the i-th mole.
	// This doesn't change the visible property of the spot
	function changeMoleSpotColor(i, color)
	{
		// Ignoring invalid moles
		if ((i < 0) || (i >= internalVars.moleCells.length)) {
			return;
		}

		internalVars.moleCells[i].spotColor = color;
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

	// Activate the animation for a successful hit
	function moleHit(moleID)
	{
		moleHitSound.play();
		internalVars.moleCells[moleID].moleHit = true;
	}

	// Activate the animation for the hit of a wrong mole
	function moleWrongHit(moleID)
	{
		moleWrongHitSound.play();
		internalVars.moleCells[moleID].moleWrongHit = true;
	}

	// Activate the animation for a missed hit
	function moleMissed(moleID)
	{
		moleMissedSound.play();
		internalVars.moleCells[moleID].moleMissed = true;
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
				console.log("Error creating cell");
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

		showCaptions: true
	}

	// The sound to play when an hit is successful
	SoundEffect {
		id: moleHitSound
		source: "qrc:///sounds/whack.wav"
		volume: container.volume
	}

	// The sound to play when the wrong mole was hit
	SoundEffect {
		id: moleWrongHitSound
		source: "qrc:///sounds/whack.wav"
		volume: container.volume
	}

	// The sound to play when a mole is missed
	SoundEffect {
		id: moleMissedSound
		source: "qrc:///sounds/slide.wav"
		volume: container.volume
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
