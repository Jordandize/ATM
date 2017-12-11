#include "Security.h"

const string Security::FINISH_WORK = "0";

Security::Security(Account& a)
:_account(a), _success(false), _attempts(a.getAttempts())
{

}

Security::~Security()
{

}

void Security::enterPINs()
{
	while(_attempts > 0 && !_success)
	{
		cout << "Enter your PIN:" << endl;
		cout << "(" << _attempts << " attempts left | finish - put '" << FINISH_WORK << "')" << endl << "> ";
		string pin;
		getline(cin, pin);
		
		if(pin    ==   FINISH_WORK)  return;
		if(_account.verifyPIN(pin)) _success = true;
		if(!_success) cout << "PIN is incorrect." << endl;

			cout << endl;
		--_attempts;
	}
}