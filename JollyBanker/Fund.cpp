#include "stdafx.h"
#include "Fund.h"

Fund::Fund(string name)
{
	pBalance = 0;
	pName = name;
}

Fund::~Fund()
{
}

bool Fund::Deposit(unsigned int amount)
{
	pBalance += (int)amount;
	return true;
}

bool Fund::Withdraw(unsigned int amount)
{
	if (amount > pBalance)
	{
		return false;
	}
	else
	{
		pBalance -= amount;
		return true;
	}


}

bool Fund::Record(string record)
{
	pRecord.push_back(record);
	return true;
}

vector<string> Fund::getRecord()
{
	return pRecord;
}

int Fund::getBalance() const
{
	return pBalance;
}

string Fund::getName() const
{
	return pName;
}

ostream& operator<<(ostream& stream, const Fund& fund)
{
	stream << "Name : " << fund.getName() << endl;
	for (int i = 0; i < fund.pRecord.size(); i++)
	{
		stream << fund.pRecord[i] << endl;
	//	stream << funds[i]->getName() << ": $"
	}
	return stream;
}