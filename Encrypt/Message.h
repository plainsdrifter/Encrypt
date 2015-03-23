//Message.h
#ifndef MESSAGE_H
#define MESSAGE_H

#define TABLESIZE 256
#define _size 1024*1024

class Message
{
	public:
		Message(const char* pStr, const char* key);
		Message(const char* pStr);
		Message();
		
		void fileInput(char* pStr);
		void consoleInput(char* pStr);

		void initTable();
		void encryptMessage();
		void decryptMessage();
		
		const char* getUnMessage() const;
		const char* getEnMessage() const;
		
		void getMessage();
		void getKey();
		void outputMessage(const char* pStr);
		
		~Message();
		
	private:
		char* pUnMessage;
		char* pEnMessage;
		char* pKey;
		char  table[TABLESIZE][TABLESIZE];

};

#endif