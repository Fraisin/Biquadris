#ifndef __NOTIF_H__
#define __NOTIF_H__
class Board;

//this is a structure that represents what kind of the notification
//the board is sending out to its observers
struct NotifInfo {
	bool nextBlockSet = false;
	bool scoreChanged = false;
	bool levelChanged = false;
	bool hiScoreChanged = false;
	bool blindOn = false;
	bool blindOff = false;
};

#endif
