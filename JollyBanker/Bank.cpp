#include "stdafx.h"
#include <sstream>
#include "Bank.h"


Bank::Bank() 
{
}

Bank::~Bank() 
{
}

int Bank::Withdraw(unsigned int id, unsigned int fund, int amount)
{
	
	Account *dummy = new Account(id, "dummy", "account");
	Account *temp;

	if (pAccounts.Retrieve(*dummy, temp))	// See if the account exists
	{
		temp->Withdraw(fund, amount);
		return true;
	}
	else
	{
		cerr << "ERROR: Account " << id << " does not exist. Transaction Failed." << endl;
		return false;
	}
}

int Bank::Deposit(unsigned int id, unsigned int fund, int amount)
{
	Account *dummy = new Account(id, "dummy", "account");
	Account *temp;

	if (pAccounts.Retrieve(*dummy, temp))
	{
		temp->Deposit(fund, amount);
		return true;
	}
	else
	{
		cerr << "ERROR: Account " << id << " does not exist. Transaction Failed." << endl;
		return false;
	}
}

bool Bank::Transfer(unsigned int sourceID, unsigned int sourceFund, int amount,
	unsigned int destID, unsigned int destFund)
{
	Account *dummy1 = new Account(sourceID, "dummy", "account");
	Account *dummy2 = new Account(destID, "dummy", "account");
	Account *source;
	Account *dest;

	if (!pAccounts.Retrieve(*dummy1, source))	//See if it exists
	{
		cerr << "ERROR: Account " << sourceID << " does not exist. Transaction Failed." << endl;
		return false;
	}
	if (!pAccounts.Retrieve(*dummy2, dest))
	{
		cerr << "ERROR: Account " << destID << " does not exist. Transaction Failed." << endl;
		return false;
	}

	
	if (source->SendTrans(sourceFund, amount, destID))	// See if funds are in source account
	{
		dest->RecieveTrans(destFund, amount, sourceID);
		return true;
	}
	else
	{
		dest->RecieveTrans(destFund, 0, sourceID);
		return false;
	}
}

bool Bank::History(unsigned int id, unsigned int fund)
{
	Account *dummy = new Account(id, "dummy", "account");
	Account *temp;

	
	if (pAccounts.Retrieve(*dummy, temp))	//See if the account exists
	{
		temp->getHistory(id, fund);
		cout << endl;
		return true;
	}
	else
	{
		cerr << "ERROR: Account " << id << " does not exist. Transaction Failed." << endl;
		return false;
	}

	return true;
}

bool Bank::Open(string nameFirst, string nameLast, unsigned int id)
{
	Account *newAccount = new Account(id, nameFirst, nameLast);

	if (pAccounts.Retrieve(*newAccount, newAccount))	//See if account exists
	{
		cerr << "ERROR: Account " << id << " is already open. Transaction refused." << endl;
		return false;
	}
	else
	{
		pAccounts.Insert(newAccount);
		return true;
	}
}

bool Bank::AddToQueue(vector<string> command)
{
	pCommandQ.push(command);
	return true;
}

bool Bank::ProcessQueue()
{
	vector<string> commands;

	while (!pCommandQ.empty())
	{
		commands = pCommandQ.front();

		if (commands[0] == "O")
		{
			Open(commands[2], commands[1], stoi(commands[3]));
		}
		else if (commands[0] == "D")
		{
			Deposit(stoi(commands[1]), stoi(commands[2]), stoi(commands[3]));
		}
		else if (commands[0] == "W")
		{
			Withdraw(stoi(commands[1]), stoi(commands[2]), stoi(commands[3]));
		}
		else if (commands[0] == "T")
		{
			Transfer(stoi(commands[1]), stoi(commands[2]), stoi(commands[3]),
				stoi(commands[4]), stoi(commands[5]));
		}
		else if (commands[0] == "H")
		{
			if ((commands[1].length() == 4) && (commands.size() == 3))
			{
				History(stoi(commands[1]), stoi(commands[2]));
			}
			else
			{
				History(stoi(commands[1]), -1);
			}
		}

		pCommandQ.pop();
	}

	cout << endl;
	cout << "Processing Complete!" << endl;
	cout << "Printing final balances..." << endl << endl;
	//Print();
	return true;
}

void Bank::Print()
{
	pAccounts.Print();
}

ostream& operator<<(ostream& stream, const Bank& bank)
{
	stream << bank;

	return stream;
}

