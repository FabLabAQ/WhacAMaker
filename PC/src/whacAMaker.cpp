#include "whacAMaker.h"

QString WhacAMaker::difficultyLevelToString(DifficultyLevel level, bool localized)
{
	QString levelName;
	if (level == WhacAMaker::Easy) {
		levelName = localized ? "Facile" : "Easy";
	} else if (level == WhacAMaker::Medium) {
		levelName = localized ? "Medio" : "Medium";
	} else if (level == WhacAMaker::Hard) {
		levelName = localized ? "Difficile" : "Hard";
	}

	return levelName;
}

QString WhacAMaker::gameTypeToString(GameType type, bool localized)
{
	QString typeName;
	if (type == WhacAMaker::Test) {
		typeName = localized ? "Test" : "Test";
	} else if (type == WhacAMaker::Classical) {
		typeName = localized ? "Classico" : "Classical";
	} else if (type == WhacAMaker::MatchColor) {
		typeName = localized ? "Colore" : "MatchColor";
	}

	return typeName;
}
