#include "ServiceTransfer.h"
#include "SessionManager.h"
#include "AccountStorage.h"

ServiceTransfer::ServiceTransfer(Account& a, SessionManager& sm)
:_account(a), _sessionManager(sm)
{

}

ServiceTransfer::~ServiceTransfer()
{

}

int ServiceTransfer::promptAmount()
{
	cout << "Enter cash amount to transfer:" << endl;
	string input;
	getline(cin, input);
	int s = -1;
	try   { s = stoi(input); }
	catch (...) { }
	cout << endl;
	return s;
}

Account& ServiceTransfer::promptAccount()
{
	cout << "Enter destionation card number for transfer:" << endl << "> ";
	string card;
	getline(cin, card);
	Account& accountTo = AccountStorage::Instance().getAccount(card);
	cout << endl;
	return accountTo;
}

void ServiceTransfer::doService()
{
	_sessionManager.securityProtocol();
	if(!_sessionManager.isSecure())
		return;

	Account * accountTo = 0;
	try
	{
		accountTo = &promptAccount();
		if(&_account == accountTo)
		{
			cout << "Error!\n";
			cout << "You can't transfer money from and to the same card." << endl;
			return;
		}
	}
	catch(const string& mess)
	{
		cout << "\nError!\n";
		cout << mess << endl;
		return;
	}

	int amount = promptAmount();
	if(amount <= 0)
	{
		cout << "Error!\n";
		cout << "Illigal cash amount!" << endl;
		return;
	}

	try
	{
		_account.withdrawal(amount);
		try
		{
			(*accountTo).replenishment(amount);
		}
		catch(...)
		{
			_account.replenishment(amount);
			cout << "Distination card error!\n" << endl;
		}
		cout << endl << "Seccess!" << endl << endl;
	}
	catch(const Account::BadAmount& ba)
	{
		cout << "Error!\n";
		cout << ba.reason() << ". Number: " << ba.number() << endl;
	}
	catch(const Account::BadAccount& ba) 
	{
		cout << "Error!\n";
		cout << ba.reason() << endl;
	}
}

string ServiceTransfer::doDescription() const
{
	return string("Transfer");
}