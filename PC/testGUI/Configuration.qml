// The panel with configuration options
import QtQuick 2.0

Item {
	id: container

	- la porta USB alla quale è connesso Arduino. È anche possibile eseguire un test di comunicazione;
	- la distanza in metri tra il puntatore laser e lo schermo;
	- la distanza in metri, sulla verticale, tra il centro dello schermo e il puntatore laser;
	- la distanza in metri, sull’asse orizzontale, tra il centro dello schermo e il puntatore laser.

	aggiungere controlli per la configurazione. Provare a vedere se è possibile mettere opacità di buttonpanel e questo a 0 ma la opacità dei figli a 1 (in modo da poter settare la immagine di sfondo solo su application)
}
