//Encrypt.cpp
#include <iostream>
#include <conio.h>

#include "Message.h"

using namespace std;

int main()
{
	Message myMessage;
	char * pTemp = new char[2];

	cout << "type: \"-d\" to decrypt or \"-e\" to encrypt message." << endl;
	fflush(stdin);
	cin.getline(pTemp, 3, '\n');

	myMessage.getMessage();
	myMessage.getKey();

	if (strcmp(pTemp, "-d") == 0)
	{	
		myMessage.decryptMessage();
		myMessage.outputMessage(myMessage.getUnMessage());
	}
	
	if (strcmp(pTemp, "-e") == 0)
	{
		myMessage.encryptMessage();
		myMessage.outputMessage(myMessage.getEnMessage());
	}

	cout << "Press any key to exit..." << endl;
	_getch();

	return 0;
}