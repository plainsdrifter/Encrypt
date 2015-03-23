//Message.cpp
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

#include "Message.h"

using namespace std;

//Default constructor
Message::Message()
{
	pUnMessage = NULL;
	pEnMessage = NULL;
	pKey = NULL;

	initTable();
}

void Message::initTable()
{
	char c;
	int id;

	for (int j = 0; j < TABLESIZE; j++)
	{
		for (int i = 0; i < TABLESIZE; i++)
		{
			id = i+j;
			c = (char)id;
			table[j][i] = c;
		}
	}
}

void Message::fileInput(char* pStr)
{
	memset(pStr, 0, _size);

	ifstream file;
	file.open("input.txt",ios::in);
	char c;
	int cnt = 0;
	if (file.is_open())
	{
		while (file.read((char*)&c, sizeof(c)))
		{
			pStr[cnt] = c;
			cnt++;
		}
	}
	else
		cout << "\"input.txt\" is not accessable!" << endl;
	file.close();
}

void Message::consoleInput(char* pStr)
{
	cout << "Enter your message (less than " << _size << " characters, end with \"ENTER\"): " << endl;
	fflush(stdin);
	cin.getline(pStr, _size, '\n');
	cout << endl;
}

void Message::encryptMessage()
{
	int across, down;
	int i, j;
	
	
	cout << "Encrypting message..." << endl;
	cout << endl << pKey << endl << pUnMessage << endl << endl;

	for (j = 0; j < (int)strlen(pEnMessage); j++)
	{
		for (i = 0; i < TABLESIZE; i++)
		{
			if( pUnMessage[j] == table[0][i] )
			{
				across = i;
				break;
			}
		}
		
		for (i = 0; i < TABLESIZE; i++)
		{	
			if( pKey[j] == table[i][0] )
			{
				down = i;
				break;
			}
		}
		
		pEnMessage[j] = table[down][across];
	}

	cout << pEnMessage << endl << endl;
}

void Message::decryptMessage()
{
	int down, across, i, j;
	
	cout << "Decrypting message..." << endl;
	cout << endl << pKey << endl << pEnMessage << endl << endl;
		
	for (j = 0; j < (int)strlen(pEnMessage); j++)
	{
		for (i = 0; i < TABLESIZE; i++)
		{
			if( pKey[j] == table[0][i] )
			{
				across = i;
				break;
			}
		}
		
		for (i = 0; i < TABLESIZE; i++)
		{
			if( pEnMessage[j] == table[i][across] )
			{
				down = i;
				break;
			}
		}
		
		pUnMessage[j] = table[down][0];
	}

	cout << pUnMessage << endl << endl;
}

//Returns uncrypted message
const char* Message::getUnMessage() const
{
	return pUnMessage;
}

//Returns encrypted message
const char* Message::getEnMessage() const
{
	return pEnMessage;
}

void Message::getMessage()
{
	char* pTemp = new char[_size];

	cout << "type: \"-c\" for console input - file input is default." << endl;
	fflush(stdin);
	cin.getline(pTemp, 3, '\n');
	if (strcmp(pTemp, "-c") == 0)
		consoleInput(pTemp);
	else
		fileInput(pTemp);
	
	pUnMessage = new char[ strlen(pTemp) + 1 ];
	strcpy_s(pUnMessage, strlen(pTemp)+1, pTemp);
	
	pEnMessage = new char[ strlen(pTemp) + 1 ];
	strcpy_s(pEnMessage, strlen(pTemp)+1, pTemp);
	
	delete[] pTemp;
}

void Message::getKey()
{	
	if(!pUnMessage)
	{
		cout << "You have to enter the message before you enter the key." << endl;
		return;
	}
	
	char* pTemp = new char[32];
	
	cout << "Enter your key (less than 32 characters, one word) that ends with \"ENTER\": " << endl;
	fflush(stdin);
	cin.getline(pTemp, 32, '\n');
	cout << endl;
	
	pKey = new char[ strlen(pUnMessage) + 1 ];
	strcpy_s(pKey, strlen(pUnMessage)+1, pUnMessage);
	
	int i, j;
	
	for (i = 0, j = 0; i < (int)strlen(pUnMessage), j < (int)strlen(pUnMessage); i++, j++)
	{	
		if(pTemp[j] && pKey[i])
		{
			pKey[i] = pTemp[j];
		}
		else if(pTemp[j] == '\0')
		{
			j = -1;
			i--;
		}
		else
			break;
	}
	
	delete[] pTemp;
}

void Message::outputMessage(const char* pStr)
{
	ofstream file;
	file.open("output.txt",ios::trunc);
	if (file.is_open())
		file.write(pStr, strlen(pStr));
	file.close();
}

//Destructor
Message::~Message()
{
	if (pUnMessage != NULL)
		delete[] pUnMessage;
	if (pEnMessage != NULL)
		delete[] pEnMessage;
	if (pKey != NULL)
		delete[] pKey;
}