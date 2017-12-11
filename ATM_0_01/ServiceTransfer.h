#ifndef _SERVICETRANSFER_H_
#define _SERVICETRANSFER_H_

#include <iostream>
using namespace std;

#include "Service.h"
#include "Account.h"

class SessionManager;
class ServiceTransfer : public Service
{
private:
	Account& _account;
	SessionManager& _sessionManager;
	Account& promptAccount();
	int promptAmount();
	virtual void doService();
	virtual string doDescription() const;
	ServiceTransfer(const ServiceTransfer&);
	ServiceTransfer& operator=(const ServiceTransfer&);

public:
	ServiceTransfer(Account&, SessionManager&);
   ~ServiceTransfer();
};

#endif //_SERVICETRANSFER_H_