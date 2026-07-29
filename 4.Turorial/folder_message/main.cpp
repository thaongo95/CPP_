#include <iostream>
#include "folder.h"
#include "message.h"


int main() {
	Message msg1("Hello"), msg2("Hi"), msg3(msg2), msg4, msg5("What"), msg6("Where");
	Folder folder1, folder2, folder3, folder4;
	msg1.save(folder1);
	msg2.save(folder1);
	msg2.save(folder2);
	msg5.save(folder3);
	msg6.save(folder4);
	//msg5.remove(folder3);
	//msg3 = msg1;
	msg4 = msg1;
	//msg5 = msg1;
	//msg6 = msg1;
	msg1 = msg2;
	//folder1.remove_message(&msg1);
	std::cout << "Folder 1 :  ";
	folder1.getMessage();
	std::cout << "Folder 2 :  ";
	folder2.getMessage();
	std::cout << "Folder 3 :  ";
	folder3.getMessage();
	std::cout << "Folder 4 :  ";
	folder4.getMessage();
}