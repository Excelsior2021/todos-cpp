#ifndef _TODOS_H_
#define _TODOS_H_

#include <vector>
#include <fstream>

#include "../todo/todo.h"

class Todos {
	std::vector<Todo> todos;
	std::fstream file;

	public:
		Todos() {};
		Todos(std::vector<Todo> &&todos): todos{todos} {};
		bool load(std::string file_name);
		void display();
		void create_todo();
		void update_todo();
		void delete_todo();
};

#endif