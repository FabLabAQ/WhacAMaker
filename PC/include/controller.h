#include <QObject>
#include <QQuickView>
#include <QVariant>

/**
 * \brief The main controller of the game
 *
 * This class takes care of controlling the game. It connects to signals from
 * QML items, starts the thread to communicate with Arduino and reads/store
 * configuration parameters and scores
 */
class Controller : public QObject
{
	Q_OBJECT

public:
	/**
	 * \brief Constructor
	 *
	 * \param view the object displaying the QML scene and starting the QML
	 *             engine
	 * \param parent the parent object
	 */
	Controller(QQuickView& view, QObject* parent = NULL);

	/**
	 * \brief Destructor
	 */
	virtual ~Controller();

protected slots:
	/**
	 * \brief This is the slot called when configuration parameters are
	 *        saved
	 *
	 * \param obj the object with configuration parameters
	 */
	void saveConfigurationParameters(/*const QVariant& obj*/);

	/**
	 * \brief This is the slot called when a player has entered its name
	 *
	 * \param name the name of the player
	 */
	void savePlayerName(const QString& name);

protected:
	/**
	 * \brief The object displaying the QML scene and starting the QML
	 *        engine
	 */
	QQuickView& m_view;
};
