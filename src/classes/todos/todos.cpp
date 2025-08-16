#include "./todos.h"

#include <iostream>
#include <sstream>

bool Todos::load() {
	file.open(filename);

	if(!file)
		return false;

	while(!file.eof()) {
		std::string description;
		bool completed;

		std::getline(file, description, ',');
		file>>completed;
		file.ignore(); //ignore newline character

		Todo todo {description, completed};
		todos.push_back(todo);
	}

	file.close();

	return true;
}

void Todos::display() {
	for(size_t i {0}; i < todos.size(); ++i) {
		size_t id = i + 1;
		todos[i].display(id);
	}
}

bool Todos::create() {
	std::string description;
	std::cout<<"Enter the todo: ";
	std::getline(std::cin, description);

	file.open(filename, std::ofstream::app);

	if(!file)
		return false;

	file<<'\n'<<description<<','<<0;
	file.close();

	std::cout<<"\nNew todo added."<<std::endl;
	Todo todo {description};
	todos.push_back(todo);

	return true;
}

void Todos::update() {
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
			std::vector<std::string> menu_items {"C - change description", selected_todo->get_status() ? "X - incomplete" : "X - complete", "Q - return to main menu"};
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

bool Todos::del() {
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
			file.open(filename, std::ifstream::in);
			std::ofstream temp_file;
			temp_file.open("temp.txt");

			if(!file || !temp_file)
				return false;

			size_t i {1};
			std::string line;

			//if todo is last line in file
			if(todo_id == todos.size()) {
				for(size_t i {1}; i < todos.size(); ++i) {
					std::getline(file, line);
					if(i == todos.size() -1)
						temp_file<<line;
					else
						temp_file<<line<<'\n';
				}
			}
			//else if todo is not last line in file
			else {
				while(std::getline(file, line)) {
				if(todo_id != i && i == todos.size())
					temp_file<<line;
				else if(todo_id != i)
					temp_file<<line<<'\n';
				++i;
				}
			}

			file.close();
			temp_file.close();

			std::remove(filename.c_str());
			std::rename("temp.txt", filename.c_str());

			todos.erase(todos.begin() + todo_id - 1);
			std::cout<<"\nTodo deleted."<<std::endl;
		}
	}
	clear_input();
	
	return true;
}