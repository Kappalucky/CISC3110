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

	string getAccountType() const
	{
		return acct_type;
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
    int acctnum_array[MAX_NUM];     //array of account numbers
    int num_accts;                  //number of accounts
    double balance_array[MAX_NUM];  //array of account balances
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
	num_accts = read_accts(acctnum_array, balance_array, MAX_NUM);
	print_accts(acctnum_array, balance_array, num_accts);

	/*	Second Part
	*	Prompts for the transaction
	*	Call function to process the requested transaction */
        menu();
		cin >> choice;

	do{
        switch (toupper(choice)) {
            case 'W':
				withdrawal(BankAccount account[], int num_accts);
				break;
            case 'D':
				deposit(BankAccount account[], int num_accts);
				break;
            case 'N':
				num_accts = new_acct(BankAccount account[], int num_accts);
				break;
            case 'B':
				balance(const BankAccount account[], int num_accts);
				break;
			case 'X':
				num_accts = delete_acct(BankAccount account[], int num_accts);
				break;
			case 'Q':
				not_done = false;
				print_accts(const BankAccount account[], int num_accts);
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
*	acctnum_array - reference to array of account numbers
*	balance_array - reference to array of account balances
*	max_accts - maximum number of active accounts allowed
Process:
*	Reads the initial database of accounts and balances
Output:
*	Fills in the initial account and balance arrays and returns the number of active accounts
*/
int read_accts(BankAccount account[], int max_accts)
{
    string line;
    ifstream infile("D:\\Users\\Shaquille\\Documents\\Program Code\\C++\\CISC3110_HW1\\CISC3110_HW1\\data\\accounts.dat");
	int acct_count = 0;

	/*while (infile >> acctnum_array[acct_count] && acct_count < max_accts)
	{
		infile >> balance_array[acct_count];
		acct_count++;
	}*/
    do
    {
        infile >> acctnum_array[acct_count] && acct_count < max_accts;
        infile >> balance_array[acct_count];
        acct_count++;
    }
    while(getline(infile, line));

	infile.close();
    return acct_count;
}

/*Function findacct:
Input:
*	acctnum_array - array of account numbers
*	num_accts - number of active accounts
*	requested_account - requested account requested_number
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
		if (acctnum_array[index] == requested_account)
			return index;
	return -1;
}

/*Function print_accts:
Input:
*	acctnum_array - reference to array of account numbers
*	balance_array - reference to array of account balances
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
		dbfile << acctnum_array[index];
		dbfile << "\t$" << balance_array[index];
		dbfile << '\n';
	}
	dbfile.flush();
	return;
}

/*Function withdrawal:
Input:
*	acctnum_array - reference to array of account numbers
*	balance_array - reference to array of account balances
*	num_accts - number of active accounts
*	outfile - reference to the output file
*	cin - reference to the "test cases" input file
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
	int requested_account;
	int index;
	double amount_to_withdraw;

	cout << '\n' << "Enter the account number: ";	//prompt for account number
	cin >> requested_account;

	index = findacct(acctnum_array, num_accts, requested_account);

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
		else if (amount_to_withdraw > balance_array[index])		//invalid amount to withdraw
		{
			outfile << '\n' << "Transaction Requested: Withdrawal" << '\n';
			outfile << "Account Number: " << requested_account << '\n';
			outfile << "Error: $" << amount_to_withdraw << " is more than current account balance" << '\n';
			outfile << "withdrawal request: $" << amount_to_withdraw << '\n';
			outfile << "Current Balance: $" << balance_array[index] << '\n';

		}
		else                                     //valid withdrawal
		{
			outfile << '\n' << "Transaction Requested: Withdrawal" << '\n';
			outfile << "Account Number: " << requested_account << '\n';
			outfile << "Old Balance: $" << balance_array[index] << '\n';
			outfile << "Amount to Withdraw: $" << amount_to_withdraw << '\n';
			balance_array[index] -= amount_to_withdraw;		//make the withdrawal
			outfile << "New Balance: $" << balance_array[index] << '\n';
		}
	}
	outfile.flush();
    return;
}


/*Function deposit:
Input:
*	acctnum_array - reference to array of account numbers
*	balance_array - reference to array of account balances
*	num_accts - number of active accounts
*	outfile - reference to the output file
*	cin - reference to the "test cases" input file
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
	int requested_account;
	int index;
	double amount_to_deposit;

	cout << '\n' << "Enter the account number: ";	//prompt for account number
	cin >> requested_account;

	index = findacct(acctnum_array, num_accts, requested_account);

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
			outfile << "Old Balance: $" << balance_array[index] << '\n';
			outfile << "Amount to Deposit: $" << amount_to_deposit << '\n';
			balance_array[index] += amount_to_deposit;		//make the deposit
			outfile << "New Balance: $" << balance_array[index] << '\n';
		}
	}
	outfile.flush();
    return;
}

/*Function new_acct:
Input:
*	acctnum_array - reference to array of account numbers
*	balance_array - reference to array of account balances
*	num_accts - number of active accounts
*	outfile - reference to the output file
*	cin - reference to the "test cases" input file
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
	int requested_account;
	int index;
	double new_account = 0;

	cout << '\n' << "Enter new account number: "; //prompt for new account number
	cin >> requested_account;

	if (!requested_account)
    {
        cout << "Invalid character. Numbers only\n";
        cin.clear();
        cin.ignore();
    }

	index = findacct(acctnum_array, num_accts, requested_account);

    if (index = -1)							  //valid account
	{
		acctnum_array[index] = requested_account;
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
*	acctnum_array - reference to array of account numbers
*	balance_array - reference to array of account balances
*	num_accts - number of active accounts
*	outfile - reference to the output file
*	cin - reference to the "test cases" input file
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
	int requested_account;
	int index;

	cout << '\n' << "Enter the account number: ";	//prompt for account number
	cin >> requested_account;

	index = findacct(const BankAccount account[], num_accts, requested_account);

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
*	acctnum_array - reference to array of account numbers
*	balance_array - reference to array of account balances
*	num_accts - number of active accounts
*	outfile - reference to the output file
*	cin - reference to the "test cases" input file
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
	int requested_account;
	int index;

	cout << '\n' << "Enter account number: ";	//prompt for account number
	cin >> requested_account;

	index = findacct(acctnum_array, num_accts, requested_account);

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
	else if (balance_array[index] > 0)			//cannot delete account with balance
	{
		outfile << '\n' << "Transaction Requested: Delete Account" << '\n';
		outfile << "Error: Account Number " << requested_account << " has a balance of $" << balance_array[index] << '\n';
	}
	else                                       //valid account
	{
		acctnum_array[index] = 0;
		num_accts--;
		outfile << '\n' << "Transaction Requested: Delete Account" << '\n';
		outfile << "Account Number: " << requested_account << " account deleted."<< '\n';
		outfile << "Current Balance: $" << balance_array[index] << '\n';
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
