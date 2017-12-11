#ifndef _SERVICEBALANCE_H
#define _SERVICEBALANCE_H

#include <iostream>
using namespace std;

#include "Service.h"
#include "Account.h"

class SessionManager;
class ServiceBalance : public Service
{
private:
	Account& _account;
	SessionManager& _sessionManager;
	virtual void doService();
	virtual string doDescription() const;
	ServiceBalance(const ServiceBalance&);
	ServiceBalance& operator=(const ServiceBalance&);

public:
	ServiceBalance(Account&, SessionManager&);
   ~ServiceBalance();
};

#endif //_SERVICEBALANCE_H