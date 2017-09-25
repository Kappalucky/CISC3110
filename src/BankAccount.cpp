// BankAccount.cpp is the BankAccount class implementation file.
#include "BankAccount.h"

BankAccount::BankAccount(double bal = 0.0)
{
	Depositor();
	//depositor.getSSN;
	acct_type = "";
	balance = bal;
	num_transactions = 0;
}

void BankAccount::setAcct_type(int type)
{
	if (type == 1)
	{
		acct_type = "Checking";
	}
	if (type == 2)
	{
		acct_type = "Savings";
	}
	else
	{
		acct_type = "CD";
	}
}

void BankAccount::makeDeposit(double amount)
{
	balance += amount;
	num_transactions++;
}

bool BankAccount::withdraw(double amount)
{
	if (balance < amount)
	{
		return false; //Not enough in the account
	}
	else
	{
		balance -= amount;
		num_transactions++;
		return true;
	}
}

double BankAccount::getBalance() const
{
	return balance;
}

int BankAccount::getTrasactions() const
{
	return num_transactions;
}

int BankAccount::getAccountNum()
{
	return acct_num;
}

string BankAccount::getName() const
{
	return depositor.getName;
}

string BankAccount::getAccountType() const
{
	return acct_type;
}

void BankAccount::setInitial(string fn, string ln, string sn, int anum, int atype, double bal)
{
	depositor.setName(fn, ln);
	depositor.setSSN(sn);
	acct_num = anum;
	setAcct_type(atype);
	balance = bal;
	num_transactions = 1;
}
