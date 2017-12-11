#ifndef _CARDREADER_H_
#define _CARDREADER_H_

#include <iostream>
#include <string>
using namespace std;

#include "Account.h"

class ATM;
class CardReader
{
private:
    ATM &_atm;
	Account * _activeAccount;
	CardReader(const CardReader&);
	CardReader& operator=
			  (const CardReader&);

public:
	CardReader(ATM&);
   ~CardReader();

	inline Account * activeAccount() const
			{ return _activeAccount; }
	inline bool isActiveAccount() const
			{ return _activeAccount; }

	void    readCard();
	void pushOutCard();

	void cardInserted_SIGNAL() const;
};

#endif //_CARDREADER_H_