#ifndef _TODO_H_
#define _TODO_H_

#include <iostream>
#include <iomanip>
#include <string>

#include "../../globals.h"
class Todo {
	size_t id;
	std::string description;
	bool completed;

	public:
		Todo(size_t id, std::string description, bool completed = false);
		void display() const;
		size_t get_id() const;
		std::string get_description() const;
		bool get_status() const;
		void change_id(const size_t &new_id);
		void change_description(const std::string &new_description);
		void change_status();
};

#endif