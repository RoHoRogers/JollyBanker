#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Bank.h"

using namespace std;

Bank *bank = new Bank();
void InputFromFile(string path);

int main()
{
	InputFromFile("BankTransIn.txt");
	bank->ProcessQueue();
	bank->Print();

	return 0;
}

void InputFromFile(string input)
{
	ifstream fin;
	string tString = "";
	vector<string> data;

	fin.open(input);

	while (!fin.eof())
	{
		fin >> tString;
		data.push_back(tString);


		if (data[0] == "T")
		{
			
			fin >> tString;			// ID
			data.push_back(tString.substr(0, tString.length() - 1));
			
			data.push_back(tString.substr(tString.length() - 1,		// Fund
				tString.length() - 1));

			fin >> tString;			// Amount
			data.push_back(tString);

			fin >> tString;			// ID
			data.push_back(tString.substr(0, tString.length() - 1));

			data.push_back(tString.substr(tString.length() - 1,			// Fund2
				tString.length() - 1));
		}
		
		else if (data[0] == "O")	// Open
		{
			
			fin >> tString;			// Last Name
			data.push_back(tString);

			fin >> tString;			// First Name
			data.push_back(tString);
			
			fin >> tString;			// ID
			data.push_back(tString);
		}
		else if (data[0] == "H")
		{
			
			fin >> tString;			// ID

			if (tString.length() == 5)
			{
				data.push_back(tString.substr(0, tString.length() - 1));
				data.push_back(tString.substr(tString.length() - 1,		// Fund1
					tString.length() - 1));
			}
			else
			{
				data.push_back(tString);
			}

		}
		
		else            // Deposit/Withdraw
		{
			fin >> tString;
			data.push_back(tString.substr(0, tString.length() - 1));

			data.push_back(tString.substr(tString.length() - 1,
				tString.length() - 1));

			fin >> tString;
			data.push_back(tString);
		}

		bank->AddToQueue(data);

		data.clear();
	}
}


