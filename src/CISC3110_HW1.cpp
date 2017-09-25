//Program CISC3110_HW1.cpp
//Bank Accounts
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> //needed for system function
using namespace std;

struct Name
{
private:
	string firstName;		//First name
	string	lastName;		//Last name

public:
	Name()
	{
		firstName = "";
		lastName = "";
	}

	void setName(string first, string last)
	{
		firstName = first;
		lastName = last;
	}

	string getName()
	{
		return firstName + " " + lastName;
	}
};

struct Depositor
{
private:
	Name name;
	string ssn;

public:
	Depositor()
	{
		Name();
		//name.getName();
		ssn = "0-0-0 - 0-0 - 0-0-0-0";
	}

	void setSSN(string social)
	{
		ssn = social;
	}

	void setName(string fn, string ln)
	{
		name.setName(fn, ln);
	}

	string getName()
	{
		return name.getName.firstName + " " + name.getName.lastName;
	}

	string getSSN()
	{
		return ssn;
	}
};

class BankAccount
{
private:
	Depositor depositor;
	string acct_type;
	int acct_num;
	int num_transactions;
	double balance;

public:
	BankAccount(double bal = 0.0)
	{
		Depositor();
		//depositor.getSSN;
		acct_type = "";
		balance = bal;
		num_transactions = 0;
	}

	void setInitial(string fn, string ln, string sn, int anum, int atype, double bal); //prototype

	void setAcct_type(int type)
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

	void makeDeposit(double amount)
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

	double getBalance() const
	{
		return balance;
	}

	int getTrasactions() const
	{
		return num_transactions;
	}

	int getAccountNum()
	{
		return acct_num;
	}

	string getName() const
	{
		return depositor.getName.firstName + " " + depositor.getName.lastName;
	}

	string getAccountType() const
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
};

// Function prototypes begin
void menu();
int read_accts(BankAccount [], int);
int findacct(const BankAccount [], int, int);
void print_accts(const BankAccount [], int);
void withdrawal(BankAccount [], int);
void deposit(BankAccount [], int);
int new_acct(BankAccount [], int);
void balance(const BankAccount [], int);
int delete_acct(BankAccount [], int);
void pause();
// Protypes end

const int MAX_NUM = 100; //Constantly will be 100

int main()
{
	BankAccount account[MAX_NUM];	//array of bank accounts
    int num_accts;                  //number of accounts
    char choice;                    //User menu choice
	bool not_done = true;			//loop control flag

	// Open account data file
	ifstream infile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\data\\accounts.dat");

	// Open output file
	ofstream outfile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\data\\output.dat");

	outfile.setf(ios::fixed, ios::floatfield); //sets decimal point to two places after ex: 12.22 rather than 12.256
	outfile.precision(2);

	/*	First Part
	*	Fill and print initial database */
	num_accts = read_accts(account, MAX_NUM);
	print_accts(account, num_accts);

	/*	Second Part
	*	Prompts for the transaction
	*	Call function to process the requested transaction */
        menu();
		cin >> choice;

	do{
        switch (toupper(choice)) {
            case 'W':
				withdrawal(account, num_accts);
				break;
            case 'D':
				deposit(account, num_accts);
				break;
            case 'N':
				num_accts = new_acct(account, num_accts);
				break;
            case 'B':
				balance(account, num_accts);
				break;
			case 'X':
				num_accts = delete_acct(account, num_accts);
				break;
			case 'Q':
				not_done = false;
				print_accts(account, num_accts);
				break;
            default:
				cout << '\n' << "Error: '" << choice << "' is an invalid selection - try again" << '\n' << '\n';
				break;
        }
		// give user a chance to look at output before printing menu
		//pause();
	}while(not_done);
	outfile.close();	// close output file

	return(0);
}

/*Function menu:
Input:
*	none
Process:
*	Prints the menu of transaction choices
Output:
*	Prints the menu of transaction choices
*/
void menu()
{
	cout << '\n' << '\n';
	cout << "Enter the letter choice based on what you would like to do:" << '\n';
	cout << "\t****************************" << '\n';
	cout << "\t*    List of Choices       *" << '\n';
	cout << "\t****************************" << '\n';
	cout << "\t     W -- Withdrawal" << '\n';
	cout << "\t     D -- Deposit" << '\n';
	cout << "\t     N -- New Account" << '\n';
	cout << "\t     B -- Balance Inquiry" << '\n';
	cout << "\t     X -- Delete Account" << '\n';
	cout << "\t     Q -- Quit" << '\n';
	cout << '\n' << "\tEnter your selection: ";
	return;
}

/*Function read_accts:
Input:
*	account - reference to array of accounts
*	max_accts - maximum number of active accounts allowed
Process:
*	Reads the initial database of accounts and balances
Output:
*	Fills in the initial accounts array and returns the number of active accounts
*/
int read_accts(BankAccount account[], int max_accts)
{
    string line;
    ifstream infile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\CISC3110_HW1\\data\\accounts.dat");
	string fn;
	string ln;
	string sn;
	int anum;
	int atype;
	int acct_count = 0;
	double bal;

    do
    {
		infile >> fn;
		infile >> ln;
		infile >> sn;
		infile >> anum;
		infile >> atype;
		infile >> bal;
		account[acct_count].setInitial(fn, ln, sn, anum, atype, bal);
		acct_count++;
    }
    while(getline(infile, line) && acct_count < max_accts);

	infile.close();

	/*while (infile >> acctnum_array[acct_count] && acct_count < max_accts)
	{
	infile >> balance_array[acct_count];
	acct_count++;
	}*/

    return acct_count;
}

/*Function findacct:
Input:
*	account - reference to array of accounts
*	num_accts - number of active accounts
*	requested_account - requested account number
Process:
*	Performs a linear search on the acct_num array for the requested account
*	Linear as MAX_NUM of accounts is 100 and there is no sorting system currently
Output:
*	If found, the index of the requested account is returned
*	Otherwise, returns -1
*/
int findacct(const BankAccount account[], int num_accts, int requested_account)
{
	for (int index = 0; index < num_accts; index++)
		if (account[index].getAccountNum = requested_account)
			return index;
	return -1;
}

/*Function print_accts:
Input:
*	account - reference to array of accounts
*	num_accts - number of active accounts
Process:
*	Prints the database of accounts and balances
Output:
*	Prints the database of accounts and balances
*/
void print_accts(const BankAccount account[], int num_accts)
{
    ofstream dbfile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\data\\bank_database.dat");
	dbfile << '\n' << '\n';
	dbfile << "\t\tDatabase of Bank Accounts" << '\n' << '\n';
	dbfile << "Account\tBalance" << '\n' << '\n';
	for (int index = 0; index < num_accts; index++)
	{
		dbfile << account[index].getAccountNum;
		dbfile << account[index].getName;
		dbfile << "\t$" << account[index].getBalance;
		dbfile << '\n';
	}
	dbfile.flush();
	return;
}

/*Function withdrawal:
Input:
*	account - reference to array of accounts
*	num_accts - number of active accounts
*	outfile - output file
Process:
*	Prompts for the requested account
*	Calls findacct() to see if the account exists
*	If the account exists, prompts for the amount to withdraw
*	If the amount is valid, it makes the withdrawal and prints the new balance
*	Otherwise, an error message is printed
Output:
*	For a valid withdrawal, the withdrawal transaction is printed
*	Otherwise, an error message is printed
*/
void withdrawal(BankAccount account[], int num_accts)
{
	ofstream outfile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\data\\output.dat");

	outfile.setf(ios::fixed, ios::floatfield); //sets decimal point to two places after ex: 12.22 rather than 12.256
	outfile.precision(2);

	int requested_account;
	int index;
	double amount_to_withdraw;

	cout << '\n' << "Enter the account number: ";	//prompt for account number
	cin >> requested_account;

	index = findacct(account, num_accts, requested_account);

	if (!requested_account)
        {
            cout << "Invalid character. Numbers only\n";
            cin.clear();
            cin.ignore();
        }

	else if (index == -1)								//invalid account
	{
		outfile << '\n' << "Transaction Requested: Withdrawal" << '\n';
		outfile << "Error: Account number " << requested_account << " does not exist" << '\n';
	}
	else                                         //valid withdrawal
	{
		cout << "Enter amount to withdraw: $";	//prompt for account to withdraw
		cin >> amount_to_withdraw;

		if (!amount_to_withdraw)
        {
            cout << "Invalid character. Numbers only\n";
            cin.clear();
            cin.ignore();
        }
		else if (amount_to_withdraw <= 0.00)			//invalid amount to withdraw
		{
			outfile << '\n' << "Transaction Requested: Withdrawal" << '\n';
			outfile << "Account Number: " << requested_account << '\n';
			outfile << "Error: $" << amount_to_withdraw << " is an invalid amount" << '\n';
		}
		//while (amount_to_withdraw > 0.00)
		else if (account[index].withdraw(amount_to_withdraw) == false)		//invalid amount to withdraw
		{
			outfile << '\n' << "Transaction Requested: Withdrawal" << '\n';
			outfile << "Account Number: " << requested_account << '\n';
			outfile << "Error: $" << amount_to_withdraw << " is more than current account balance" << '\n';
			outfile << "withdrawal request: $" << amount_to_withdraw << '\n';
			outfile << "Current Balance: $" << account[index].getBalance << '\n';

		}
		else                                     //valid withdrawal
		{
			outfile << '\n' << "Transaction Requested: Withdrawal" << '\n';
			outfile << "Account Number: " << requested_account << '\n';
			outfile << "Old Balance: $" << account[index].getBalance << '\n';
			outfile << "Amount to Withdraw: $" << amount_to_withdraw << '\n';
			account[index].withdraw(amount_to_withdraw);		//make the withdrawal
			outfile << "New Balance: $" << account[index].getBalance << '\n';
		}
	}
	outfile.flush();
    return;
}


/*Function deposit:
Input:
*	account - reference to array of accounts
*	num_accts - number of active accounts
*	outfile - output file
Process:
*	Prompts for the requested account
*	Calls findacct() to see if the account exists
*	If the account exists, prompts for the amount to deposit
*	If the amout is valid, it makes the deposit and prints the new balance
*	Otherwise, an error message is printed
Output:
*	For a valid deposit, the deposit transaction is printed
*	Otherwise, an error message is printed
*/
void deposit(BankAccount account[], int num_accts)
{
	ofstream outfile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\data\\output.dat");

	outfile.setf(ios::fixed, ios::floatfield); //sets decimal point to two places after ex: 12.22 rather than 12.256
	outfile.precision(2);

	int requested_account;
	int index;
	double amount_to_deposit;

	cout << '\n' << "Enter the account number: ";	//prompt for account number
	cin >> requested_account;

	index = findacct(account, num_accts, requested_account);

	if (!requested_account)
    {
        cout << "Invalid character. Numbers only\n";
        cin.clear();
        cin.ignore();
    }
	else if (index == -1)								//invalid account
	{
		outfile << '\n' << "Transaction Requested: Deposit" << '\n';
		outfile << "Error: Account number " << requested_account << " does not exist" << '\n';
	}
	else                                             //valid deposit
	{
		cout << "Enter amount to deposit: $";		//prompt for account to deposit
		cin >> amount_to_deposit;

		if (!amount_to_deposit)
		{
			cout << "Invalid character. Numbers only\n";
			cin.clear();
			cin.ignore();
		}

		else if (amount_to_deposit <= 0.00)				//invalid amount to deposit
		{
			outfile << '\n' << "Transaction Requested: Deposit" << '\n';
			outfile << "Account Number: " << requested_account << '\n';
			outfile << "Error: $" << amount_to_deposit << " is an invalid amount" << '\n';
		}
		else                                         //valid deposit
		{
			outfile << '\n' << "Transaction Requested: Deposit" << '\n';
			outfile << "Account Number: " << requested_account << '\n';
			outfile << "Old Balance: $" << account[index].getBalance << '\n';
			outfile << "Amount to Deposit: $" << amount_to_deposit << '\n';
			account[index].makeDeposit(amount_to_deposit);		//make the deposit
			outfile << "New Balance: $" << account[index].getBalance << '\n';
		}
	}
	outfile.flush();
    return;
}

/*Function new_acct:
Input:
*	account - reference to array of accounts
*	num_accts - number of active accounts
*	outfile - output file
Process:
*	Prompts for a new account number
*	Calls findacct() to see if the account exists
*	If the account exists, an error message is printed
*	Otherwise add account with amount of 0
Output:
*	Returns new number of accounts
*/
int new_acct(BankAccount account[], int num_accts)
{
	ofstream outfile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\data\\output.dat");

	outfile.setf(ios::fixed, ios::floatfield); //sets decimal point to two places after ex: 12.22 rather than 12.256
	outfile.precision(2);

	string fn;
	string ln;
	string sn;
	int anum;
	int atype;
	int index;
	int acct_count = 0;
	int requested_account;
	double bal;
	double new_account = 0;

	cout << '\n' << "Enter new account number: "; //prompt for new account number
	cin >> requested_account;

	if (!requested_account)
    {
        cout << "Invalid character. Numbers only\n";
        cin.clear();
        cin.ignore();
    }

	index = findacct(account, num_accts, requested_account);

    if (index = -1)							  //valid account
	{
		requested_account = anum;

		cout << "Enter First and last name to be associated with account: " << '\n';
		cout << "First: ";
		cin >> fn;
		cout << '\n' << "Last: ";
		cin >> ln;

		cout << "Enter Social Security Number to be associated with name: ";
		cin >> sn;
		cout << '\n';

		cout << "Choose account type based on number in menu: " << '\n';
		cout << "1 - Checking" << '\n';
		cout << "2 - Savings" << '\n';
		cout << "3 - CD" << '\n';
		cout << ": ";
		cin >> atype;

		cout << "Enter ammount to deposit: ";
		cin >> bal;
		cout << '\n';

		account[num_accts+1].setInitial(fn, ln, sn, anum, atype, bal);
        num_accts++;

		outfile << '\n' << "Transaction Requested: New Account" << '\n';
		outfile << "Account Number: " << requested_account << " created."<< '\n';
		//outfile << "Current Balance: $" << balance_array[index] << '\n';
	}
	else if (index != -1)                                          //invalid account
	{
		outfile << '\n' << "Transaction requested: New Account" << '\n';
		outfile << "Error: Account number " << requested_account << " already exist" << '\n';
	}
	outfile.flush();
    return num_accts;
}

/*Function balance:
Input:
*	account - reference to array of accounts
*	num_accts - number of active accounts
*	outfile - output file
Process:
*	Prompts for the requested account
*	Calls findacct() to see if the account exists
*	If the account exists, the balance is printed
*	Otherwise, an error message is printed
Output:
*	If the account exists, the balance is printed
*	Otherwise, an error message is printed
*/
void balance(const BankAccount account[], int num_accts)
{
	ofstream outfile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\data\\output.dat");

	outfile.setf(ios::fixed, ios::floatfield); //sets decimal point to two places after ex: 12.22 rather than 12.256
	outfile.precision(2);

	int requested_account;
	int index;

	cout << '\n' << "Enter the account number: ";	//prompt for account number
	cin >> requested_account;

	index = findacct(account, num_accts, requested_account);

	if (!requested_account)
    {
        cout << "Invalid character. Numbers only\n";
        cin.clear();
        cin.ignore();
    }
	else if (index == -1)								//invalid account
	{
		outfile << '\n' << "Transaction Requested: Balance Inquiry" << '\n';
		outfile << "Error: Account number " << requested_account << " does not exist" << '\n';
		//add goto and break to 'Begin:' to loop for user to repeat
	}
	else                                             //valid account
	{
		outfile << '\n' << "Transaction Requested: Balance Inquiry" << '\n';
		outfile << "Account Number: " << requested_account << '\n';
		outfile << "Current Balance: $" << account[index].getBalance << '\n';
	}
	outfile.flush();
	return;
}

/*Function delete_acct:
Input:
*	account - reference to array of accounts
*	num_accts - number of active accounts
*	outfile - output file
Process:
*	Prompts user for an account number
*	If account does not exist, an error message is printed
*	If account has a balance over 0, an error message is printed
*	Otherwise delete account
Output:
*	Returns new number of accounts
*/
int delete_acct(BankAccount account[], int num_accts)
{
	ofstream outfile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\data\\output.dat");

	outfile.setf(ios::fixed, ios::floatfield); //sets decimal point to two places after ex: 12.22 rather than 12.256
	outfile.precision(2);

	int requested_account;
	int index;

	cout << '\n' << "Enter account number: ";	//prompt for account number
	cin >> requested_account;

	index = findacct(account, num_accts, requested_account);

	if (!requested_account)
    {
        cout << "Invalid character. Numbers only\n";
        cin.clear();
        cin.ignore();
    }
	else if (index == -1)							//invalid account
	{
		outfile << '\n' << "Transaction Requested: Delete Account" << '\n';
		outfile << "Error: Account Number " << requested_account << " does not exist" << '\n';
	}
	else if (account[index].getBalance > 0)			//cannot delete account with balance
	{
		outfile << '\n' << "Transaction Requested: Delete Account" << '\n';
		outfile << "Error: Account Number " << requested_account << " has a balance of $" << account[index].getBalance << '\n';
	}
	else                                       //valid account
	{
		num_accts--;
		outfile << '\n' << "Transaction Requested: Delete Account" << '\n';
		outfile << "Account Number: " << requested_account << " account deleted."<< '\n';
	}
	outfile.flush();
	return num_accts;

}

/* Function pause:
Input:
*	none
Process :
*	Pauses system
Output :
*	none
*/
void pause(void)
{
	system("pause");
	return;
}
