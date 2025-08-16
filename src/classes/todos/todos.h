#ifndef _TODOS_H_
#define _TODOS_H_

#include <vector>
#include <fstream>

#include "../todo/todo.h"

class Todos {
	std::vector<Todo> todos;
	std::fstream file;
	std::string file_name;

	public:
		Todos(std::string file_name): file_name{file_name} {};
		bool load();
		void display();
		bool create();
		void update();
		void del();
};

#endif