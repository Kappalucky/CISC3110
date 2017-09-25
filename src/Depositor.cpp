// Depositor.cpp is the Depositor struct implementation file.
#include "Depositor.h"

Depositor::Depositor()
{
	Name();
	//name.getName();
	ssn = "0-0-0 - 0-0 - 0-0-0-0";
}

void Depositor::setSSN(string social)
{
	ssn = social;
}

void Depositor::setName(string fn, string ln)
{
	name.setName(fn, ln);
}

string Depositor::getName()
{
	return name.getName;
}

string Depositor::getSSN()
{
	return ssn;
}