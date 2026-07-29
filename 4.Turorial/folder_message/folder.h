#pragma once
#include <set>
#include "message.h"
#include <iostream>

class Folder {
	std::set<Message*> point_to_Messages;
public:
	void add_message(Message* msg);
	void remove_message(Message* msg);
	void getMessage();
};
