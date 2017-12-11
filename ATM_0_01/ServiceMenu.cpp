#include "ServiceMenu.h"
#include "SessionManager.h"

ServiceMenu::ServiceMenu(SessionManager& sm)
:_sessionManager(sm)
{

}

ServiceMenu::~ServiceMenu()
{

}

void ServiceMenu::doService()
{
	cout << "Enter service number:" << endl;
	cout << (*this);
	cout << "> ";

	string input;
	getline(cin, input);
	int s = 0;
	try   { s = stoi(input); }
	catch (...) { }

	if(s >= SessionManager::SERVICES_AMOUNT || s < 1)
	{
		cout << "Service number '" << s << "' is incorrect! Try again." << endl << endl;
		doService();
	}
	else
	{
		_sessionManager.setService(s);
	}
}

string ServiceMenu::doDescription() const
{
	return string("Menu");
}

const Service * const * const ServiceMenu::getServices() const
{
	return _sessionManager.getServices();
}

ostream& operator<<(ostream& os, const ServiceMenu& sm)
{
	const Service * const * const services = sm.getServices();
	for(int i = 1; i < SessionManager::SERVICES_AMOUNT; i++)
	{
		os << '[' << i << ']' << " # " << (*services[i]).description() << endl;
	}
	return os;
}