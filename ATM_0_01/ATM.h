#ifndef _ATM_H_
#define _ATM_H_

#include <iostream>
using namespace std;

#include "CardReader.h"
#include "Dispenser.h"
#include "SessionManager.h"
#include "AccountStorage.h"

class ATM
{
private:
	static int _freeId;
	const  int _id;

	CardReader _cardReader;
	Dispenser  _dispenser;
	SessionManager * _sessionManager;

	ATM(const ATM&);				//this is not using
	ATM& operator=(const ATM&);		//this is not using

public:
	ATM();
   ~ATM();
	inline int getId() const { return _id; }
	inline Dispenser & getDispenser () { return _dispenser ; }
	inline CardReader& getCardReader() { return _cardReader; }


	//Dispenser's API
	inline bool isCorrectAmount(int amount)
								   const { return _dispenser.isCorrectAmount(amount); }
	inline bool isBlocked       () const { return _dispenser.isBlocked(            ); }
	inline bool * availableNotes() const { return _dispenser.availableNotes(       ); }

	inline map<Notes, int> outcash(int total)
			{ return _dispenser.outcash(total); }
	inline map<Notes, int> incash (int _100 = 1000, int _200 = 1000, int _500 = 400)
			{ return _dispenser.incash(_100, _200, _500); }


	//CardReader's API
	inline void    readCard() { _cardReader.readCard(   ); }
	inline void pushOutCard() { _cardReader.pushOutCard(); }
	inline Account * activeAccount() const { return _cardReader.activeAccount(  ); }
	inline bool    isActiveAccount() const { return _cardReader.isActiveAccount(); }


	//Start session
	void cardInserted_SLOT();
	//Close session
	void closeSession();
};

ostream& operator<<(ostream&, const ATM&);

#endif //_ATM_H_