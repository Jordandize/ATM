#ifndef _SERVICEMENU_H_H
#define _SERVICEMENU_H_H

#include <iostream>
#include <string>
using namespace std;

#include "Service.h"

class SessionManager;
class ServiceMenu : public Service
{
private:
	SessionManager& _sessionManager;
	virtual void doService();
	virtual string doDescription() const;
	ServiceMenu(const ServiceMenu&);
	ServiceMenu& operator=(const ServiceMenu&);

public:
	ServiceMenu(SessionManager&);
   ~ServiceMenu();
	
   const Service * const * const getServices() const;
};

ostream& operator<<(ostream&, const ServiceMenu&);

#endif //_SERVICEMENU_H_H