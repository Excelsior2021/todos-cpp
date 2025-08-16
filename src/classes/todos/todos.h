#ifndef _TODOS_H_
#define _TODOS_H_

#include <vector>

#include "../todo/todo.h"

class Todos {
	std::vector<Todo> todos;

	public:
		Todos() {};
		Todos(std::vector<Todo> &&todos): todos{todos} {};
		std::vector<Todo>* get_todos();
		void display();
		void create_todo();
		void update_todo();
		void delete_todo();
};

#endif