#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

#include "utils/utils.h"
#include "classes/todo/todo.h"
#include "classes/todos/todos.h"

int main() {
	//Sample todos
	Todo todo1 {"create todo app"};
	Todo todo2 {"learn C++"};
	Todo todo3 {"get a programming job"};

	Todos todos {std::vector<Todo> {todo1, todo2, todo3}};

	std::vector<std::string> menu_items {"C - create todo", "U - update todo", "D - delete todo", "Q - quit"};

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
				todos.create_todo();
				break;
			}
			case 'U': 
			case 'u': {
				todos.update_todo();
				break;
			}
			case 'D': 
			case 'd': {
				todos.delete_todo();
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