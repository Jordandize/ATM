#include "ServiceExit.h"
#include "SessionManager.h"

ServiceExit::ServiceExit(SessionManager& sm)
:_sessionManager(sm)
{

}

ServiceExit::~ServiceExit()
{

}

void ServiceExit::doService()
{
	_sessionManager.closeSession();
}

string ServiceExit::doDescription() const
{
	return string("Exit");
}