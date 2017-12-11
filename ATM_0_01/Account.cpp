#include "Account.h"
#include <iostream>

const int Account::DEFAULT_ATTEMPTS = 3;
const int Account::REFRESH_PIN_TIME = 30000;

Account::Account(const string& owner,
				 const string& PIN,
				 const string& number,
				 const int balance)
:_number(number), _owner(owner), _PIN(PIN), _balance(balance),
_attempts(DEFAULT_ATTEMPTS), _blocked(false), _timer(new Timer()),
_lastTry((*_timer).getCurrentTime())
{ }

Account::~Account()
{
   delete _timer;
}

Account::Account(const Account& a)
:_number(a._number), _owner(a._owner), _PIN(a._PIN), _balance(a._balance),
_attempts(a._attempts), _blocked(a._blocked), _timer(new Timer()),
_lastTry(a._lastTry)
{ }

Account& Account::operator=(const Account &a)
{
	if(this == &a)
		return *this;
	
	_number   = a._number;
	_owner    = a._owner; 
	_PIN      = a._PIN;
	_balance  = a._balance;
	_attempts = a._attempts;
	_blocked  = a._blocked;
	_lastTry  = a._lastTry;

	return *this;
}

bool Account::verifyPIN(const string& PIN)
{
	if(_blocked) false;

	if(_PIN == PIN)
	{
		_attempts = DEFAULT_ATTEMPTS;
		return true;
	}
	
	_lastTry = _timer->getCurrentTime();
	if(!--_attempts)
	{
		_blocked = true;
		throw BadPIN(string("You used all the attempts to enter PIN. Account has been blocked"));
	}
	
	return false;
}

int Account::getAttempts()
{
	if(_blocked) return 0;
	
	if(_attempts != DEFAULT_ATTEMPTS)
	{
		DWORD nowTime = _timer->getCurrentTime();
		if(nowTime - _lastTry > REFRESH_PIN_TIME)
			_attempts = DEFAULT_ATTEMPTS;
	}

	return _attempts; 
}

void Account::increase(const int sum)
{
	if(_blocked)
		throw BadAccount(string("Fail to increase balance amount: account is blocked"));

	_balance += sum;
}

void Account::decrease(const int sum)
{
	if(_blocked)
		throw BadAccount(string("Fail to decrease balance amount: account is blocked"));

	_balance -= sum;
}

void Account::withdrawal(const int sum)
{
	if(sum < 0)
		throw BadAmount(string("Illegal cash amount to withdraw (negative)"), sum);
	if(_balance < sum)
		throw BadAmount(string("Not enought money to withdraw"), sum);
	decrease(sum);
}

void Account::replenishment(const int sum)
{
	if(sum < 0)
		throw BadAmount(string("Illegal cash amount to replenish (negative)"), sum);
	increase(sum);
}

void Account::transferTo(Account& a, const int sum) {
    withdrawal(sum);
	a.replenishment(sum);
}


ostream& operator<<(ostream& os, const Account& a)
{
	return os << a.owner() << " : " << a.number() << " : " << a.balance() << endl;
}


