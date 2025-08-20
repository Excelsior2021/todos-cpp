#ifndef _TODO_H_
#define _TODO_H_

#include <string>

#include "../../utils/utils.h"

class Todo {
	size_t id;
	std::string description;
	bool completed;

	public:
		Todo(size_t id, std::string description, bool completed = false): 
			id {id}, description {description}, completed{completed} {}
		std::string get_description() const {
			return description;
		};
		void change_id(size_t new_id) {
			id = new_id;
		}
		void display() const;
		bool get_status() const {
			return completed;
		}
		void change_description(std::string new_description) {
			description = new_description;
		}
		void change_status() {
			completed = !completed;
		}
};

#endif