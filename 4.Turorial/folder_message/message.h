#pragma once
#include <string>
#include <vector>
#include <set>
#include "folder.h"
#include <memory>

class Message {
	friend class Folder;
	std::string content;
	std::set<Folder*> point_to_Folders;
	void add_all_folder(const Message&);
	void remove_all_folder();
public:
	Message();
	Message(const std::string& s);
	Message(const Message& other);
	Message& operator=(const Message& other);
	void save(Folder& folder);
	void remove(Folder& folder);
	~Message();
};