#include "./todos.h"

#include <iostream>
#include <sstream>


void Todos::display() {
	for(size_t i {0}; i < todos.size(); ++i) {
		size_t id = i + 1;
		todos[i].display(id);
	}
}

void Todos::create_todo() {
	std::string description;
	std::cout<<"Enter the todo: ";
	std::getline(std::cin, description);
	std::cout<<"\nNew todo added."<<std::endl;
	Todo todo {description};
	todos.push_back(todo);
}

void Todos::update_todo() {
	std::string user_input;
	size_t todo_id;
	
	std::cout<<"Please enter the ID of the todo you want to update or enter q to quit: ";
	std::getline(std::cin, user_input);

	while(user_input != "q" && user_input != "Q") {
		std::istringstream iss(user_input);
		iss>>todo_id;

		if(!iss>>todo_id) {
			std::cin.clear();
			std::cout<<"\nPlease enter a valid ID or enter q to quit: ";
			std::getline(std::cin, user_input);
		} else if(!(todo_id > 0 && todo_id <= todos.size())) {
			std::cout<<"\nNo todo with that ID exists!";
			std::cout<<"\n\nPlease enter a valid ID or enter q to quit: ";
			std::getline(std::cin, user_input);
		} else {
			char selection;		
			Todo* selected_todo = &todos[todo_id - 1];
			std::vector<std::string> menu_items {"C - change description", selected_todo->get_status() ? "X - incomplete" : "X - Complete", "Q - return to main menu"};
			std::cout<<'\n';
			header("UPDATE TODO");
			selected_todo->display(todo_id);
			display_menu(menu_items);
			std::cout<<"\nSelect an option from the options above: ";
			std::cin>>selection;

			switch (selection) {
				case 'C':
				case 'c': {
					std::string new_description;
					clear_input();
					std::cout<<"\nPlease enter the new description: ";
					std::getline(std::cin, new_description);
					selected_todo->change_description(new_description);
					std::cout<<"\nTodo description changed."<<std::endl;
					break;
				}
				case 'X':
				case 'x': {
					selected_todo->change_status();
					std::cout<<"\nTodo status changed."<<std::endl;
					break;
				}
				case 'Q':
				case 'q': {
					user_input = selection; //to exit loop
					break;
				}
				default: {
					clear_input();
					std::cout<<"\nUpdate Todo: **Not a valid option!**"<<std::endl;
					break;
				}
			}
		};
	}

	std::cout<<"\nReturning to main menu..."<<std::endl;
}

void Todos::delete_todo() {
	size_t todo_id;
	std::cout<<"Please enter ID of the todo you want to delete: ";
	if(!(std::cin>>todo_id)) {
		std::cin.clear();
		std::cout<<"\nPlease enter a valid ID!\n"<<std::endl;
	} else if(!(todo_id > 0 && todo_id <= todos.size())) {
		std::cout<<"\nNo todo with that ID exists!\n"<<std::endl;
	} else {
		char confirmation;
		clear_input();
		std::cout<<"\nDelete todo (ID: "<<todo_id<<"). Are you sure? (Y/N): ";
		std::cin>>confirmation;
		if(confirmation != 'Y' && confirmation != 'y') {
			std::cout<<"\nTodo not deleted."<<std::endl;
		} else {
			todos.erase(todos.begin() + todo_id - 1);
			std::cout<<"\nTodo deleted."<<std::endl;
		}
	}
	clear_input();
}