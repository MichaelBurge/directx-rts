// strings.cpp: implementation of the strings class.
//
//////////////////////////////////////////////////////////////////////

#include "main.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

strings::strings()
{
	text=NULL;
}
strings::strings(char *initialize) {
	text=NULL;
	*this=initialize;
}
strings::~strings()
{
	delete [] text;
}
strings &strings::operator=(char *string) {
	if (text) 
		delete [] text;
	char *temp=new char[strlen(string)+1];
	strcpy(temp,string);
	text = temp;//Copy the string to spot, and point to spot. Doesn't affect normal string if this happens
	return *this;
}
strings strings::operator+(char *string) {
	char *buffer = new char[strlen(text)+strlen(string)+1];
	strcpy(buffer,text);
	strcpy(buffer+strlen(text),string);
	return strings(buffer);
}
strings &strings::operator+=(char *string) {
	return *this=*this+string;
}
strings strings::operator+(int number) {
	int temp = 0;
	while (pow(temp,2)<number) temp++;
	char *buffer = new char[temp*3+1];
	itoa(number,buffer,10);
	return *this+buffer;
}