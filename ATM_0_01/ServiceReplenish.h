#ifndef _SERVICEREPLENISH_H_
#define _SERVICEREPLENISH_H_

#include <iostream>
using namespace std;

#include "Service.h"
#include "Account.h"

class SessionManager;
class ServiceReplenish : public Service
{
private:
	Account& _account;
	SessionManager& _sessionManager;
	virtual void doService();
	virtual string doDescription() const;
	ServiceReplenish(const ServiceReplenish&);
	ServiceReplenish& operator=(const ServiceReplenish&);

public:
	ServiceReplenish(Account&, SessionManager&);
   ~ServiceReplenish();
};

#endif //_SERVICEREPLENISH_H_