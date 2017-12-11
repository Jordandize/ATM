#ifndef _SERVICEEXIT_H_
#define _SERVICEEXIT_H_

#include <iostream>
using namespace std;

#include "Service.h"

class SessionManager;
class ServiceExit : public Service
{
private:
	SessionManager& _sessionManager;
	virtual void doService();
	virtual string doDescription() const;
	ServiceExit(const ServiceExit&);
	ServiceExit& operator=(const ServiceExit&);

public:
	ServiceExit(SessionManager& sm);
   ~ServiceExit();
};

#endif //_SERVICEEXIT_H_