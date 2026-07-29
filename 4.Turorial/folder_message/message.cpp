#include "folder.h"

Message::Message():content(std::string()){

}

Message::Message(const std::string& s):content(s){

}

Message::Message(const Message& other)
	:content(other.content), point_to_Folders(other.point_to_Folders)
{
	add_all_folder(other);
}

Message& Message::operator=(const Message& other) {
	remove_all_folder();
	content = other.content;
	point_to_Folders = other.point_to_Folders;
	add_all_folder(other);
	return *this;
}

void Message::add_all_folder(const Message& msg) {
	for (auto value : msg.point_to_Folders) {
		value->add_message(this);
	}
}
void Message::remove_all_folder() {
	for (auto value : point_to_Folders) {
		value->remove_message(this);
	}
	point_to_Folders.clear();
}

void Message::save(Folder& folder) {
	folder.add_message(this);
	point_to_Folders.insert(&folder);
}
void Message::remove(Folder& folder) {
	folder.remove_message(this);
}



Message::~Message() {
	point_to_Folders.clear();
}