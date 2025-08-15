#ifndef _TODO_H_
#define _TODO_H_

#include <string>

#include "../../utils/utils.h"

class Todo {
	std::string description;
	bool completed {false};

	public:
		Todo(std::string description): description {description} {}
		std::string get_description() const {
			return description;
		};
		void display(size_t id);
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