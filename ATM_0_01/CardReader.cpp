#include "CardReader.h"
#include "ATM.h"

CardReader::CardReader(ATM& atm)
:_activeAccount(0), _atm(atm)
{

}

CardReader::~CardReader()
{
	_activeAccount = 0;
}

void CardReader::readCard()
{
	cout << "PUT CARD NUMBER:" << endl << "> ";
	string card;
	getline(cin, card);
	_activeAccount = &AccountStorage::Instance().getAccount(card);
	cout << endl;
}

void CardReader::pushOutCard()
{ 
	_activeAccount = 0;
}

void CardReader::cardInserted_SIGNAL() const
{
	_atm.cardInserted_SLOT();
}