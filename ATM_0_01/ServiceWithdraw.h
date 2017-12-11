#ifndef _SERVICEWITHDRAW_H_
#define _SERVICEWITHDRAW_H_

#include <iostream>
using namespace std;

#include "Service.h"
#include "Account.h"

class SessionManager;
class ServiceWithdraw : public Service
{
private:
	Account& _account;
	SessionManager& _sessionManager;
	void printAvailable() const;
	virtual void doService();
	virtual string doDescription() const;
	ServiceWithdraw(const ServiceWithdraw&);
	ServiceWithdraw& operator=(const ServiceWithdraw&);

public:
	ServiceWithdraw(Account&, SessionManager&);
   ~ServiceWithdraw();
};

#endif //_SERVICEWITHDRAW_H_