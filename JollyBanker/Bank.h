#pragma once

#ifndef BANK_H
#define BANK_H

#include <string>
#include <iostream>
#include <queue>
#include "BSTree.h"
#include "Account.h"

using namespace std;

struct AccData
{
	string command;
	string first;
	string last;
	unsigned int id1;
	unsigned int fund1;
	unsigned int id2;
	unsigned int fund2;
};

class Bank
{
	friend ostream& operator<<(ostream& stream, const Bank& bank);
public:
	Bank();
	~Bank();

	int Withdraw(unsigned int id, unsigned int fund, int amount);
	int Deposit(unsigned int id, unsigned int fund, int amount);
	
	bool Open(string nameFirst, string nameLast, unsigned int id);
	bool History(unsigned int id, unsigned int fund);
	bool Transfer(unsigned int sourceID, unsigned int destID, int amount,
		unsigned int sourceFund, unsigned int destFund);
	
	bool AddToQueue(vector<string> command);
	bool ProcessQueue();
	void Print();



private:
	BSTree pAccounts;
	queue<vector<string>> pCommandQ;
};

#endif