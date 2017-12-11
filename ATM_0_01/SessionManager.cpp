#include "SessionManager.h"

const int SessionManager::SERVICES_AMOUNT = 6;

SessionManager::SessionManager(Account& a, ATM& atm):
_account(a), _atm(atm), _services(new Service*[SERVICES_AMOUNT]),
_activeService(0), _secure(true)
{
	initServices();
}

SessionManager::~SessionManager()
{
	for(int i = 0; i < SERVICES_AMOUNT; i++)
		delete _services[i];
	delete [] _services;
}

void SessionManager::initServices()
{
	_services[0] = new ServiceMenu(*this);
	_services[1] = new ServiceBalance(_account, *this);
	_services[2] = new ServiceReplenish(_account, *this);
	_services[3] = new ServiceWithdraw(_account, *this);
	_services[4] = new ServiceTransfer(_account, *this);
	_services[SERVICES_AMOUNT - 1] = new ServiceExit(*this);
}

void SessionManager::securityProtocol()
{
	Security security(_account);
	security.enterPINs();

	if(security.isSuccess())
	{
		_secure = true;
	}
	else
	{
		_secure = false;
	}
}

void SessionManager::startSession()
{
	if(_account) throw Account::BadAccount(string("Fail to start session: account is blocked"));

	cout << endl << "--------------- Welcome ---------------" << endl << endl;
	securityProtocol();

	while(_secure)
	{
		promptService();
		runService();
	}
}

void SessionManager::closeSession()
{
	_secure = false;
}

void SessionManager::setService(int n) {
	if(n > 0 && n < SERVICES_AMOUNT) _activeService = n;
	else                             _activeService = 0;
}

void SessionManager::runService()
{
	Service& service = *_services[_activeService];
	cout << endl << "<<<<<<<<<<<< " << service.description() << " >>>>>>>>>>>>" << endl << endl;
	service.service();
}

void SessionManager::promptService()
{
	setService(0);
	runService();
}