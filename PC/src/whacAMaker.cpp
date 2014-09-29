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
