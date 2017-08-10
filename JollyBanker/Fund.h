#pragma once
#ifndef FUND_H
#define FUND_H

#include <string>
#include <vector>

using namespace std;

class Fund
{
	friend ostream& operator<<(ostream& stream, const Fund& fund);
public:
	Fund(string name);
	~Fund();

	bool Deposit(unsigned int amount);
	bool Withdraw(unsigned int amount);
	bool Record(string record);
	vector<string> getRecord();

	int getBalance() const;
	string getName() const;

private:
	int pBalance;
	string pName;
	vector<string> pRecord;
};

#endif
