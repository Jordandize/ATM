#include "ATM.h"

int ATM::_freeId = 1;

ATM::ATM()
:_id(_freeId++), _cardReader(*this), _dispenser(*this), _sessionManager(0)
{

}

ATM::~ATM()
{
	delete _sessionManager;
}

void ATM::cardInserted_SLOT()
{
	if(_sessionManager)
		throw "Something is going wrong in _sessionManager";

	try
	{
		_cardReader.readCard();

		_sessionManager = new SessionManager(*_cardReader.activeAccount(), *this);
		_sessionManager->startSession();
	}
	catch(const Account::BadAccount& ba)
	{
		cout << "Error!" << endl;
		cout << ba.reason() << '.' << endl << endl;
	}
	catch(const Account::BadPIN& bp)
	{
		cout << "Error!" << endl;
		cout << bp.reason() << '.' << endl << endl;
	}
	catch(const string& mess)
	{
		cout << mess << endl << endl;
	}

	closeSession();
	_cardReader.pushOutCard();
}

void ATM::closeSession()
{
	delete _sessionManager;
	_sessionManager = 0;
}

ostream& operator<<(ostream& os, const ATM& atm)
{
	return os << "ATM {id=" << atm.getId() << "}";
}