// Name.cpp is the Name struct implementation file.
#include "Name.h"

Name::Name()
{
	firstName = "";
	lastName = "";
}

void Name::setName(string first, string last)
{
	firstName = first;
	lastName = last;
}

string Name::getName()
{
	return firstName + " " + lastName;
}
