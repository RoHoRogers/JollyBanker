#include "stdafx.h"
#include "Account.h"

Account::Account(unsigned int id, string first, string last)
{
	pID = id;
	pNameFirst = first;
	pNameLast = last;

	pFunds[0] = new Fund("Money Market");
	pFunds[1] = new Fund("Prime Money Market");
	pFunds[2] = new Fund("Long-Term Bond");
	pFunds[3] = new Fund("Short-Term Bond");
	pFunds[4] = new Fund("500 Index Fund");
	pFunds[5] = new Fund("Capital Value Fund");
	pFunds[6] = new Fund("Growth Equity Fund");
	pFunds[7] = new Fund("Growth Index Fund");
	pFunds[8] = new Fund("Value Fund");
	pFunds[9] = new Fund("Stock Index Fund");

}

Account::~Account()
{
}

bool Account::Deposit(int fund, unsigned int amount)
{
	string status = "D " + to_string(pID) + to_string(fund) + " " + to_string(amount);

	if (HelpDeposit(fund, amount))
	{
		pFunds[fund]->Record(status);
		return true;
	}
	else
	{
		pFunds[fund]->Record(status + " (FAILED)");
		return false;
	}
}

bool Account::Withdraw(int fund, unsigned int amount)
{
	string status = "W " + to_string(pID) + to_string(fund) + " " + to_string(amount);

	if (HelpWithdraw(fund, amount))
	{
		pFunds[fund]->Record(status);
		return true;
	}
	else
	{
		cerr << "ERROR: Not enough funds to complete " << amount << " Withdrawal from "<< pNameFirst << " " << pNameLast << endl;
		pFunds[fund]->Record(status + " (FAILED)");
		return false;
	}
}

bool Account::SendTrans(unsigned int fund, unsigned int amount, unsigned int destID)
{
	string status = "T " + to_string(pID) + to_string(fund) + " " + to_string(amount) + " " + to_string(destID);
	if (HelpWithdraw(fund, amount))
	{	
		pFunds[fund]->Record(status);
		return true;
	}
	else
	{
		pFunds[fund]->Record(status + " (FAILED)");
		cerr << "ERROR: Not enough funds to complete " + amount << " transfer from " << pNameFirst << " " << pNameLast << endl;
		return false;
	}
}

bool Account::RecieveTrans(unsigned int fund, unsigned int amount, unsigned int sourceID)
{
	string status = "T " + to_string(pID) + to_string(fund) + " " + to_string(amount) + " " + to_string(sourceID);
	if (HelpDeposit(fund, amount))
	{
		pFunds[fund]->Record(status);
		return true;
	}
	else
	{
		pFunds[fund]->Record(status + " (FAILED)");
		//cerr << "ERROR: Not enough funds to complete " + amount << " transfer" << endl;
		return false;
	}
}

void Account::getHistory(unsigned int id, int fund) const
{
	vector<string> temp;

	if (fund == -1)
	{
		cout << "Transaction History for " << getName() << "." << endl;
		for (int i = 0; i < 10; i++)
		{
			temp = pFunds[i]->getRecord();
			if (temp.size() != 0)
			{
				cout << pFunds[i]->getName() << ": $";
				cout << pFunds[i]->getBalance() << endl;

				for (auto it = temp.begin(); it < temp.end(); it++)
				{
					cout << "  " + *it << endl;
				}
			}
		}
	}
	else
	{
		cout << "Transaction History for " + getName();
		cout << " " << pFunds[fund]->getName() << ": $" << pFunds[fund]->getBalance() << endl;

		temp = pFunds[fund]->getRecord();
		for (auto it = temp.begin(); it < temp.end(); it++)
		{
			cout << "  " + *it << endl;
		}

	}
}

string Account::getName() const
{
	return pNameLast + " " + pNameFirst;
}

unsigned int Account::getID() const
{
	return pID;
}

bool Account::FundCover(int fund, int amount)
{
	int altFund;

	switch (fund)
	{
	case 0:
		altFund = 1;
		break;
	case 1:
		altFund = 0;
		break;
	case 2:
		altFund = 3;
		break;
	case 3:
		altFund = 2;
		break;
	default:
		return false;
	}

	
	int balance = pFunds[fund]->getBalance() - amount;	//See what the balance would be in advance

	if (balance < 0)	//borrow from other fund if need
	{
		if (pFunds[altFund]->getBalance() >= abs(balance))	//Check to see if can withdrawl
		{
			if (pFunds[altFund]->Withdraw(abs(balance)))
			{
				pFunds[fund]->Deposit(abs(balance));
			}
			else
			{
				return false;
			}
			return pFunds[fund]->Withdraw(amount);
		}
	}
	else
	{
		return pFunds[fund]->Withdraw(amount);
	}
	return true;
}

bool Account::HelpDeposit(int fund, unsigned int amount)
{
	if (fund >= 0 && fund < 10)
	{
		pFunds[fund]->Deposit(amount);
		return true;
	}
	else
	{
		return false;
	}
}

bool Account::HelpWithdraw(int fund, unsigned int amount)
{
	if (fund < 0 || fund > 9)
	{
		cerr << "ERROR: " << fund <<  " is not a Valid Fund Input" << endl;
		return false;
	}

	if (fund == 0)
	{
		FundCover(fund, amount);
	}
	else if (fund == 1)
	{
		FundCover(fund, amount);
	}
	else if (fund == 2)
	{
		FundCover(fund, amount);
	}
	else if (fund == 3)
	{
		FundCover(fund, amount);
	}

	else
	{
		if (pFunds[fund]->Withdraw(amount))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool Account::operator==(const Account &other) const
{
	if (this->getID() == other.getID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Account::operator<(const Account &other) const
{
	if (this->getID() < other.getID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& stream, const Account& account)
{

	stream << "Balances for " << account.getName() << ":" << endl;

	for (int i = 0; i < 10; i++)
	{	
		vector<string> tempR = account.pFunds[i]->getRecord();
		string tempN = account.pFunds[i]->getName();
		int tempB = account.pFunds[i]->getBalance();

		stream << tempN << ": $" << tempB << endl;
		//stream << tempB << endl
	}
	return stream;
}