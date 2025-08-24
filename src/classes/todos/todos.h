#ifndef _TODOS_H_
#define _TODOS_H_

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <algorithm>

#include "../../utils/utils.h"
#include "../todo/todo.h"

class Todos {
	std::vector<Todo> todos;
	std::fstream file;
	std::string filename;
	std::string tempfile_path {"data/temp.txt"};

	public:
		Todos(std::string filename): filename{filename} {};
		bool load();
		void display();
		bool create();
		bool update();
		bool del();
};

#endif