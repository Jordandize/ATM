#include "ServiceReplenish.h"
#include "SessionManager.h"

ServiceReplenish::ServiceReplenish(Account& a, SessionManager& sm)
:_account(a), _sessionManager(sm)
{

}

ServiceReplenish::~ServiceReplenish()
{

}

void ServiceReplenish::doService()
{
	cout << "Enter cash amount:" << endl;
	
	string input;
	getline(cin, input);
	int s = -1;
	try   { s = stoi(input); }
	catch (...) { }

	try
	{
		_account.replenishment(s);
		cout << endl << "Success!" << endl << endl;
	}
	catch(const Account::BadAmount& ba)
	{
		cout << "Error!" << endl;
		cout << ba.reason() << ". Value: " << ba.number() << endl;
	}
}

string ServiceReplenish::doDescription() const
{
	return string("Replenish");
}