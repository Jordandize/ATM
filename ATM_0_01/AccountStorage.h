#ifndef _ACCOUNT_STORAGE_H
#define _ACCOUNT_STORAGE_H

#include <map>
#include "Account.h"

class AccountStorage
{
private:
	AccountStorage():_accounts() {      }
   ~AccountStorage()             {      }
	AccountStorage(const AccountStorage&);
	AccountStorage& operator=
				  (const AccountStorage&);

	mutable map<string, Account> _accounts;

public:
	static AccountStorage& Instance()
	{
		static AccountStorage storage;
		return storage;
	}

	void delAccount(const string&);
	void addAccount(const Account&);

	Account& getAccount(const string&);
};

#endif;