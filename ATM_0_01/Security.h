#ifndef _SECURITY_H_
#define _SECURITY_H_

#include <iostream>
#include <string>
using namespace std;

#include "Account.h"

class Security
{
private:
	const static string FINISH_WORK;
	int _attempts;
	bool _success;
	Account& _account;

	Security(const Security&);
	Security& operator=(const Security&);

public:
	Security(Account&);
   ~Security();
    void enterPINs();
	inline bool isSuccess() const { return _success; }
};

#endif //_SECURITY_H_