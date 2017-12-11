#include "Cassette.h"

const int Cassette::MAX_INCASH   = 1500000;
const int Cassette::MAX_NOTESSET = 40;
const int Cassette::MIN_AMOUNT   = 2000;

Cassette::Cassette():
_notes(), _blocked(true)
{

}

Cassette::~Cassette()
{

}

map<Notes, int> Cassette::incash(int _100, int _200, int _500)
{
	if(_100*100 + _200*200 + _500*500 > MAX_INCASH)
		throw BadAmount();
	
	setBlocked(false);

	map<Notes, int> lastBalance(_notes);
	_notes.clear();
	_notes[Notes::_100] = _100;
	_notes[Notes::_200] = _200;
	_notes[Notes::_500] = _500;

	return lastBalance;
}

map<Notes, int> Cassette::outcash(int total)
{
	try
	{
		map<Notes, int> cashOutSet(countCashSet(total));	//count set of notes to cash out
		checkLegalCashSet(cashOutSet);						//the set must have not more then MAX_NOTESSET notes
		deductCashSet(cashOutSet);							//decrease cassette amount notes by set of notes to cashout
		return cashOutSet;
	}
	catch(const BadAmount& ba)
	{
		if(cassetteBalance() < MIN_AMOUNT) setBlocked(true);
		throw ba;
	}
	catch(const BadSet& bs)
	{
		throw bs;
	}
}

map<Notes, int> Cassette::countCashSet(int total)
{
	int amount = total;
	int _500(0), 
		_200(0), 
		_100(0);

	while(total >= 500 && has500(_500))
		{ _500++; total -= 500; }
	if(_500 > 0 && total % 200 != 0 && !has100())
		{ _500--; total += 500; }
	while(total >= 200 && has200(_200))
		{ _200++; total -= 200; }
	while(total >= 100 && has100(_100))
		{ _100++; total -= 100; }

	if(total != 0)
		throw BadAmount(string("ATM hasn't required set of banknotes."), amount);

	map<Notes, int> cashSet;
	cashSet[Notes::_100] = _100;
	cashSet[Notes::_200] = _200;
	cashSet[Notes::_500] = _500;
	return cashSet;
}

void Cassette::checkLegalCashSet(map<Notes, int>& cashSet)
{
	if(cashSet[Notes::_100] +
	   cashSet[Notes::_200] +
	   cashSet[Notes::_500] > MAX_NOTESSET)
	{
		throw BadSet(string("Banknote set to outcash is too big."));
	}
}

void Cassette::deductCashSet(map<Notes, int>& cashSet)
{
	if(!enoughToCashOut(cashSet))
		throw BadSet(string("Cassete hasn't enough banknotes to withdraw this cashset."));

	_notes[Notes::_100] = _notes[Notes::_100] - cashSet[Notes::_100];
	_notes[Notes::_200] = _notes[Notes::_200] - cashSet[Notes::_200];
	_notes[Notes::_500] = _notes[Notes::_500] - cashSet[Notes::_500];
}

bool Cassette::enoughToCashOut(map<Notes, int>& cashSet)
{
	if(_notes[Notes::_100] >= cashSet[Notes::_100] &&
	   _notes[Notes::_200] >= cashSet[Notes::_200] &&
	   _notes[Notes::_500] >= cashSet[Notes::_500])
		return true;
	
	return false;
}

int Cassette::cassetteBalance()
{
	int total = 0;
	total += _notes[Notes::_100] * 100;
	total += _notes[Notes::_200] * 200;
	total += _notes[Notes::_500] * 500;
	return total;
}

ostream& operator<<(ostream& os, const Cassette& c)
{
	typedef map<Notes,int>::iterator it_type;
	os << "{ ";
	for(it_type iterator = c.getNotesMap().begin(); iterator != c.getNotesMap().end(); iterator++) {
		os << iterator->first << "=" << iterator->second << " ";
	}
	os << "}";
	return os;
}

ostream& operator<<(ostream& os, map<Notes, int>& m)
{
	typedef map<Notes,int>::iterator it_type;
	os << "{ ";
	for(it_type iterator = m.begin(); iterator != m.end(); iterator++) {
		os << iterator->first << "=" << iterator->second << " ";
	}
	os << "}";
	return os;
}