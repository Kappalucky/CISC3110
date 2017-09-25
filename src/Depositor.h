// Depositor.h is the Depositor struct specification file.
#ifndef DEPOSITOR_H
#define DEPOSITOR_H

#include "Name.h"
//Depositor struct declarations
struct Depositor
{
private:
	Name name;	//name to come from Name struct "Name.h"
	string ssn; //Social Security Number
public:
	Depositor();
	void setSSN(string social);
	void setName(string fn, string ln);
	string getName();
	string getSSN();
};
#endif // !DEPOSITOR_H