#include "whacAMaker.h"

QString WhacAMaker::difficultyLevelToString(DifficultyLevel level)
{
	QString levelName;
	if (level == WhacAMaker::Easy) {
		levelName = "Easy";
	} else if (level == WhacAMaker::Medium) {
		levelName = "Medium";
	} else if (level == WhacAMaker::Hard) {
		levelName = "Hard";
	}

	return levelName;
}

QString WhacAMaker::gameTypeToString(GameType type)
{
	QString typeName;
	if (type == WhacAMaker::Test) {
		typeName = "Test";
	} else if (type == WhacAMaker::Classical) {
		typeName = "Classical";
	} else if (type == WhacAMaker::MatchColor) {
		typeName = "MatchColor";
	}

	return typeName;
}
