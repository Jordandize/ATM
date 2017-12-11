#include <iostream>
#include <string>

#include "ATM.h"
#include "AccountStorage.h"
#include "Account.h"

using namespace std;

int main(void)
{
	AccountStorage& storage = AccountStorage::Instance();

	Account a0("Kostya", "1111", "11");
	Account a1("Nastya", "2222", "22");
	Account a2("Jordan", "3333", "33");

	storage.addAccount(a0);
	storage.addAccount(a1);
	storage.addAccount(a2);
	
	ATM atm;
	map<Notes, int> lastCassetteBalance(atm.incash());
	
	while(true)
	{
		try
		{ 
			atm.cardInserted_SLOT();
		}
		catch (char * mess)
		{
			cout << mess << endl;
		}
	}

	return 0;
}
