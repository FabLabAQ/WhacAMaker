#include "whackAMaker.h"

QString WhackAMaker::difficultyLevelToString(DifficultyLevel level)
{
	QString levelName;
	if (level == WhackAMaker::Easy) {
		levelName = "Easy";
	} else if (level == WhackAMaker::Medium) {
		levelName = "Medium";
	} else if (level == WhackAMaker::Hard) {
		levelName = "Hard";
	}

	return levelName;
}
