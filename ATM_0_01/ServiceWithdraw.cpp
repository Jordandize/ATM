#include "ServiceWithdraw.h"
#include "SessionManager.h"
#include "ATM.h"

ServiceWithdraw::ServiceWithdraw(Account& a, SessionManager& sm)
:_account(a), _sessionManager(sm)
{

}

ServiceWithdraw::~ServiceWithdraw()
{

}

void ServiceWithdraw::printAvailable() const
{

	bool * avail = _sessionManager.atmAPI().availableNotes();

	cout << "Available banknotes:";
	if(avail[0]) cout << " 100"; if(avail[1] && avail[0]) cout << ',';
	if(avail[1]) cout << " 200"; if(avail[2] && avail[1]) cout << ',';
	if(avail[2]) cout << " 500";
	if(!avail[0] && !avail[1] && !avail[2])
		cout << " none";
	cout << "." << endl << endl;

	delete [] avail;
}

void ServiceWithdraw::doService()
{
	//check blocked cassette
	if(_sessionManager.atmAPI().isBlocked())
	{
		cout << "Withdraw service is not available at moment." << endl;
		cout << "Please, use another ATM to withdraw you money." << endl;
		return;
	}

	//enter PINs
	_sessionManager.securityProtocol();
	if(!_sessionManager.isSecure())
		return;

	//print out guide message and get cash amount
	printAvailable();
	cout << "Enter cash amount:" << endl;
	string input;
	getline(cin, input);
	int s = -1;
	try   { s = stoi(input); }
	catch (...) { }
	cout << endl;
	
	//try withdraw cash amount
	if(_sessionManager.atmAPI().isCorrectAmount(s))
	{
		try
		{
			_account.withdrawal(s);
			map<Notes, int> withdrawSet(_sessionManager.atmAPI().outcash(s));
		
			cout << "Success!" << endl;
			cout << withdrawSet << endl;
		}
		catch(const Account::BadAccount& ba)
		{
			cout << "Error!" << endl;
			cout << ba.reason() << '.' << endl;
		}
		catch(const Account::BadAmount& ba)
		{
			cout << "Error!" << endl;
			cout << ba.reason() << ". Number: " << ba.number() << endl;
		}
		catch(const Cassette::BadAmount& ba)
		{
			_account.replenishment(s); //if operation isn't successfull, go money back
			cout << "Error!" << endl;
			cout << ba.reason() << ". Number: " << ba.number() << endl;
		}
		catch(const Cassette::BadSet& bs)
		{
			_account.replenishment(s); //if operation isn't successfull, go money back
			cout << "Error!" << endl;
			cout << bs.reason() << endl;
		}
	}
	else
	{
		cout << "Error!\n";
		cout << "Amount must be multiply to available banlnotes denomination." << endl;
	}
}

string ServiceWithdraw::doDescription() const
{
	return string("Withdraw");
}