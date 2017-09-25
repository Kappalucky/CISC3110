// BankAccount.h is the BankAccount class specification file.
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Depositor.h"

//BankAccount class declarations
class BankAccount
{
private:
	Depositor depositor;
	string acct_type;
	int acct_num;
	int num_transactions;
	double balance;
public:
	BankAccount(double bal = 0.0);
	void setInitial(string fn, string ln, string sn, int anum, int atype, double bal);
	void setAcct_type(int type);
	void makeDeposit(double amount);
	bool withdraw(double amount);
	double getBalance() const;
	int getTrasactions();
	int getAccountNum() const;
	string getName() const;
	string getAccountType();
	string getSSN();

};
#endif // !BANKACCOUNT_H