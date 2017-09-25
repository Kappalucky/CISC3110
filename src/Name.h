//// Name.h is the Name struct specification file.
#ifndef NAME_H
#define NAME_H

#include <string>
using std::string;
//Name struct declarations
struct Name
{
private:
	string firstName;	//First Name
	string lastName;	//Last Name
public:
	Name();
	void setName(string first, string last);
	string getName();
};
#endif // !NAME_H