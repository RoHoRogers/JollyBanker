//#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>
#include "Fund.h"

using namespace std;

class Account
{
	friend ostream& operator<<(ostream& stream, const Account& account);
public:
	Account(unsigned int id, string first, string last);
	~Account();

	bool Deposit(int fund, unsigned int amount);
	bool Withdraw(int fund, unsigned int amount);

	bool SendTrans(unsigned int fund, unsigned int amount, unsigned int destID);
	bool RecieveTrans(unsigned int fund, unsigned int amount, unsigned int sourceID);

	void getHistory(unsigned int id, int fund) const;
	unsigned int getID() const;
	string getName() const;

	bool operator==(const Account &other) const;
	bool operator<(const Account &other) const;
	//bool operator<<(ostream &);

private:
	unsigned int pID;
	string pNameFirst;
	string pNameLast;
	Fund *pFunds[10];
	vector <string> pHistory;

	bool FundCover(int fund, int amount);
	bool HelpDeposit(int fund, unsigned int amount);
	bool HelpWithdraw(int fund, unsigned int amount);
};

#endif