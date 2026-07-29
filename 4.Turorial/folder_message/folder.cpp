
#include "folder.h"

void Folder::add_message(Message* msg) {
	point_to_Messages.insert(msg);
}

void Folder::remove_message(Message* msg)
{	
	auto it = point_to_Messages.find(msg);
	if (it != point_to_Messages.end())
		point_to_Messages.erase(it);
	else std::cout << "not found" << std::endl;
}

void Folder::getMessage() {
	for (auto msg : point_to_Messages) {
		std::cout << msg->content << std::endl;
	}
}