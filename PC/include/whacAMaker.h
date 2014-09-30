#ifndef __WHAC_A_MAKER_H__
#define __WHAC_A_MAKER_H__

#include <QObject>
#include <QString>

/**
 * \brief The class with constants and enumerations used in the game
 *
 * This is more like a namespace for game-specific constants and enumerations
 */
class WhacAMaker : public QObject
{
	Q_OBJECT
	Q_ENUMS(DifficultyLevel)
	Q_ENUMS(GameType)

public:
	/**
	 * \brief The difficulty levels
	 */
	enum DifficultyLevel {
		Easy,
		Medium,
		Hard
	};

	/**
	 * \brief The game type
	 */
	enum GameType {
		Test,
		Classical,
		MatchColor
	};

	/**
	 * \brief Returns a string representation of the given DifficultyLevel
	 *
	 * \return a string representation of the given DifficultyLevel
	 */
	static QString difficultyLevelToString(DifficultyLevel level);

	/**
	 * \brief Returns a string representation of the given GameType
	 *
	 * \return a string representation of the given GameType
	 */
	static QString gameTypeToString(GameType type);
};

#endif
