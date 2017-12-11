#include "ServiceBalance.h"
#include "SessionManager.h"

ServiceBalance::ServiceBalance(Account& a, SessionManager& sm)
	:_account(a), _sessionManager(sm)
{

}

ServiceBalance::~ServiceBalance()
{

}

void ServiceBalance::doService()
{
	_sessionManager.securityProtocol();
	if(!_sessionManager.isSecure())
		return;

	cout << "Account balance:" << endl;
	cout << _account.balance() << endl;
}

string ServiceBalance::doDescription() const
{
	return string("Show Balance");
}