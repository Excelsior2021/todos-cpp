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
		Todo(size_t id, std::string description, bool completed = false): 
			id {id}, description {description}, completed{completed} {}
		void display() const;
		std::string get_description() const
		{
			return description;
		}
		bool get_status() const
		{
			return completed;
		}
		void change_id(size_t new_id)
		{
			id = new_id;
		}
		void change_description(std::string new_description)
		{
			description = new_description;
		}
		void change_status()
		{
			completed = !completed;
		}
};

#endif