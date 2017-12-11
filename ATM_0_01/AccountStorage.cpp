#include "AccountStorage.h"

void AccountStorage::addAccount(const Account& a)
{
	_accounts[a.number()] = a;
}

void AccountStorage::delAccount(const string& num) 
{
	_accounts.erase(num);
}

Account& AccountStorage::getAccount(const string& num)
{
	map<string, Account>::iterator it = _accounts.find(num);
	if(it == _accounts.end()) 
		throw string("Not found account with number: ") + string(num);
	return _accounts[num];
}