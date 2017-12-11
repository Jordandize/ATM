#ifndef _DISPENSER_H_
#define _DISPENSER_H_

#include <iostream>
#include <map>
using namespace std;

#include "Constants.h"
#include "Cassette.h"

class ATM;
class Dispenser
{
private:
	static const int MIN_100_AMOUNT;
	static const int MIN_200_AMOUNT;
	static const int MIN_500_AMOUNT;
	ATM &_atm;
	Cassette _cassette;
	bool _blocked;
	Dispenser(const Dispenser&);
	Dispenser& operator=
		     (const Dispenser&);

public:
	Dispenser(ATM&);
   ~Dispenser();

    inline bool isBlocked() const  { return _cassette.isBlocked(); }
    inline Cassette& getCassette() { return _cassette; }
	//mark notes (100, 200, 500) available to outcash
	bool *  availableNotes() const;
	bool isCorrectAmount(int) const;

	map<Notes, int> incash (int _100 = 1000, int _200 = 1000, int _500 = 400)
			{ return _cassette.incash(_100, _200, _500); }
	map<Notes, int> outcash(int total)//fix
			{ return _cassette.outcash(total); }
};

ostream& operator<<(ostream&, Dispenser&);

#endif //_DISPENSER_H_