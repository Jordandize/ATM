#ifndef _SESSIONMANAGER_H_
#define _SESSIONMANAGER_H_

#include <iostream>
using namespace std;

#include "Account.h"
#include "Service.h"
#include "Security.h"
#include "ServiceExit.h"
#include "ServiceMenu.h"
#include "ServiceBalance.h"
#include "ServiceWithdraw.h"
#include "ServiceTransfer.h"
#include "ServiceReplenish.h"

class ATM;
class SessionManager
{
private:
	Account& _account;
	ATM& _atm;
	Service ** _services;
	int _activeService;
	bool _secure;
	void initServices();
	SessionManager(const SessionManager&);
	SessionManager& operator=(const SessionManager&);

public:
	static const int SERVICES_AMOUNT;
	SessionManager(Account&, ATM&);
   ~SessionManager();
    
    void securityProtocol();
	void startSession();
	void closeSession();
	void setService(int);
	void runService();
	void promptService();

	inline ATM& atmAPI() { return _atm; }
	inline bool isSecure() const { return _secure; }
    inline const Service * const * const getServices() const { return _services; }
};

#endif //_SESSIONMANAGER_H_