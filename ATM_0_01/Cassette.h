#ifndef _CASSETTE_H_
#define _CASSETTE_H_

#include <iostream>
#include <map>
using namespace std;

#include "Constants.h"

class Cassette
{
private:
	const static int MAX_INCASH;	//max value of cash that cassette can hold
	const static int MAX_NOTESSET;	//max amount of notes in a set to cashout
	const static int MIN_AMOUNT;    //min amount of cash for cassette's work
	mutable map<Notes, int> _notes;	//cassette's notes storage
	bool _blocked;					//mark outcash function as non effective untill next incashment
	
	int cassetteBalance();                      //count total cash amount in cassette
	map<Notes, int> countCashSet(int);			//return a set of notes to cashout
	void checkLegalCashSet(map<Notes, int>&);   //notes amount to cashout must be less then 41
	void deductCashSet    (map<Notes, int>&);	//decrease amount of notes in cassette
	bool enoughToCashOut  (map<Notes, int>&);	//cassette must have enough notes to cashout
	inline void setBlocked(bool state)
			{ _blocked = state; }
	
	Cassette(const Cassette&);	//this is not using
	Cassette& operator=
			(const Cassette&);	//this is not using

public:
	Cassette();
   ~Cassette();

	map<Notes, int> incash (int _100 = 1000, int _200 = 1000, int _500 = 400);
	map<Notes, int> outcash(int);
	
	inline map<Notes,int>& getNotesMap() const { return _notes; }
	inline bool has100(int x = 0) const { return _notes[_100] - x > 0; }
	inline bool has200(int x = 0) const { return _notes[_200] - x > 0; }
	inline bool has500(int x = 0) const { return _notes[_500] - x > 0; }
	inline bool isBlocked() const { return _blocked; }

	class BadAmount;
	class BadSet;
};

class Cassette::BadAmount
{
private:
	const string _reason;
	const int _number;

public:
	BadAmount(string& reason = string(), const int num = 0)
	:_reason(reason), _number(num)
	{ }

	~BadAmount() { }

	inline const string& reason() const { return _reason; }
	inline const int     number() const { return _number; }
};

class Cassette::BadSet
{
private:
	const string _reason;

public:
	BadSet(string& reason = string())
	:_reason(reason)
	{ }

	~BadSet() { }

	inline const string& reason() const { return _reason; }
};

ostream& operator<<(ostream&, const Cassette&);
ostream& operator<<(ostream&, map<Notes, int>&);

#endif //_CASSETTE_H_





















//help me x_x
//hello from KOS BAR OLE 2017