#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <array>
#include <limits>

#include "globals.h"
#include "utils/utils.h"
#include "classes/todo/todo.h"
#include "classes/todos/todos.h"
#include "classes/exceptions/file_exception.h"

int main(int argc, char* argv[]) {
	Todos todos {argv[1] ? argv[1]  : "./data/todos.txt"};

	try
	{
		todos.load();
	}
	catch(const std::exception& e)
	{
		std::cerr<<e.what();
		std::cout<<"\nClosing app."<<std::endl;
		return 1;
	}

	std::array<std::string, 4> menu_items {"C - create todo", "U - update todo", "D - delete todo", "Q - quit"};

	char selection {};

	while(selection != 'Q' && selection != 'q') {
		std::cout<<'\n';
		header("TODOS");
		todos.display();
		display_menu(menu_items);
		std::cout<<"\nSelect an option from the options above: ";
		std::cin>>selection;
		std::cout<<'\n';
		clear_input();

		switch (selection) {
			case 'C': 
			case 'c': {
				todos.create();
				break;
			}
			case 'U': 
			case 'u': {
				todos.update();
				break;
			}
			case 'D': 
			case 'd': {
				todos.del();
				break;
			}
			case 'Q':
			case 'q': {
				std::cout<<"Closing app.\n"<<std:: endl;
				break;
			}
			default: {
				std::cout<<"\nMenu: **Not a valid option!**\n"<<std::endl;
			}
		}
	};

	return 0;
}