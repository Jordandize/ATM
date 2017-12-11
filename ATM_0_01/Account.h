#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;

class Account
{
private:
	static const int DEFAULT_ATTEMPTS;
	static const int REFRESH_PIN_TIME;

	class Timer;
    Timer * _timer;
	DWORD _lastTry;

	string _number;
	string _owner;
	string _PIN;
	
	int _balance;
	int _attempts;
	bool _blocked;

	void increase(const int sum);
	void decrease(const int sum);

public:
    class BadAmount;
	class BadAccount;
	class BadPIN;

	Account(const string& owner  = "NULL",
		    const string& PIN    = "0000",
			const string& number = "NULL",
			const int    balance = 0    );

    Account(const Account&);
   ~Account();
    Account& operator=(const Account&);

	inline int    balance  () const { return _balance; }
	inline string owner    () const { return _owner;   }
	inline string number   () const { return _number;  }
	inline operator bool   () const { return _blocked; }

	int  getAttempts();
	bool verifyPIN(const string&);

	void replenishment(const int);
	void withdrawal   (const int);
	void transferTo   (Account& a, const int);
};

class Account::BadAmount
{
private:
	const string _reason;
	const int _number;

public:
	BadAmount(string& reason = string(), const int num = 0)
	:_reason(reason), _number(num)
	{ return; }

	~BadAmount() { }

	inline const string& reason() const { return _reason; }
	inline const int     number() const { return _number; }
};

class Account::BadAccount
{
private:
	const string _reason;

public:
	BadAccount(string& reason = string())
	:_reason(reason)
	{ return; }

	~BadAccount() { }

	inline const string& reason() const { return _reason; }
};

class Account::BadPIN
{
private:
	const string _reason;

public:
	BadPIN(string& reason = string())
	:_reason(reason)
	{ return; }

	~BadPIN() { }

	inline const string& reason() const { return _reason; }
};

class Account::Timer
{
public:
	Timer() { }
   ~Timer() { }
	inline DWORD getCurrentTime() { return GetTickCount(); }
};

ostream& operator<<(ostream&, const Account&);

#endif //_ACCOUNT_H_