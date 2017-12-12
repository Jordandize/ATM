#include "Dispenser.h"
#include "ATM.h"

const int Dispenser::MIN_100_AMOUNT = 5;
const int Dispenser::MIN_200_AMOUNT = 3;
const int Dispenser::MIN_500_AMOUNT = 2;

Dispenser::Dispenser(ATM& atm)
:_atm(atm), _cassette()
{

}

Dispenser::~Dispenser()
{

}

bool * Dispenser::availableNotes() const
{
	bool * available = new bool[3];
	available[0] = _cassette.has100(MIN_100_AMOUNT - 1);
	available[1] = _cassette.has200(MIN_200_AMOUNT - 1);
	available[2] = _cassette.has500(MIN_500_AMOUNT - 1);
	return available;
}

bool Dispenser::isCorrectAmount(int total) const
{
	if(total <= 0) return false;

	bool correct = false;
	bool * avail = availableNotes();

	if( (avail[0] && !(total % 100)) ||
	    (avail[1] && !(total % 200)) ||
	    (avail[2] && !(total % 500)) )
	{
		correct = true;
	}

	delete [] avail;
	return correct;
}

ostream& operator<<(ostream& os, Dispenser& d)
{
	return os << d.getCassette();
}