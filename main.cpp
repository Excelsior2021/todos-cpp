#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

//Program constants
const unsigned int DISPLAY_WIDTH {50};
const unsigned int COLUMN_BUFFER {3}; //For separation between Todo table columns
const unsigned int TODO_ID_COLUMN_WIDTH {3 + COLUMN_BUFFER}; //3 because assumming max todo id will be 3 digits e.g. 999
const unsigned int STATUS_COLUMN_WIDTH {10 + COLUMN_BUFFER}; //10 because 'incomplete' is 10 chars long. 'complete' has 8 chars
const unsigned int TODO_COLUMN_WIDTH {DISPLAY_WIDTH - TODO_ID_COLUMN_WIDTH - STATUS_COLUMN_WIDTH};
const std::string strikethrough_start{"\e[9m"};
const std::string strikethrough_stop{"\e[29m"};

class Todo {
	std::string description;
	bool completed {false};

	public:
		Todo(std::string description): description {description} {}
		std::string get_description() const {
			return description;
		};
		bool get_status() const {
			return completed;
		}
		void change_status() {
			completed = !completed;
		}
};

//Util for console UI alignment, not a feature of the app
void ruler(unsigned int length) {
	std::string digits {"1234567890"};
	for(size_t i {0}; i < length; ++i)
		std::cout<<digits;
	std::cout<<std::endl;
}

//Clears the input buffer
void clear_input() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void display_linebreak() {
	std::cout<<std::setw(DISPLAY_WIDTH)<<std::setfill('-')<<""<<std::endl<<std::setfill(' ');
}

void header(const std::string HEADING) {
	const auto HEADING_WIDTH {(DISPLAY_WIDTH/2)+(HEADING.length()/2)};
	std::cout<<std::setw(HEADING_WIDTH)<<HEADING<<std::endl;
	display_linebreak();
}

void display_todo(const Todo todo, size_t id) {
	const auto TODO_DESCRIPTION_WIDTH {todo.get_description().length()};
	std::cout<<std::left<<std::setw(TODO_ID_COLUMN_WIDTH)<<id
	<<(todo.get_status() ? strikethrough_start : "")<<std::setw(TODO_DESCRIPTION_WIDTH)<<todo.get_description()<<(todo.get_status() ? strikethrough_stop : "")
	<<std::setw(TODO_COLUMN_WIDTH - TODO_DESCRIPTION_WIDTH)<<""
	<<std::right<<std::setw(STATUS_COLUMN_WIDTH)<<(todo.get_status() ? "complete" : "incomplete")<<std::endl;
}

void display_todos(std::vector<Todo> const &todos) {
	for(size_t i {0}; i < todos.size(); ++i) {
		size_t id = i + 1;
		display_todo(todos[i], id);
	}
}

void display_menu(std::vector<std::string> menu_items) {
	display_linebreak();
	for(auto item:menu_items)
		std::cout<<item<<std::endl;
}

void create_todo(std::vector<Todo> &todos) {
	std::string description;
	std::cout<<"Enter the todo: ";
	std::getline(std::cin, description);
	std::cout<<"\nNew todo added.\n"<<std::endl;
	Todo todo {description};
	todos.push_back(todo);
}

void update_todo(std::vector<Todo> &todos) {
	unsigned int todo_id;
	std::cout<<"Please enter ID of the todo you want to update: ";
	if(!(std::cin>>todo_id)) {
		std::cin.clear();
		std::cout<<"\nPlease enter a valid ID!\n"<<std::endl;
	} else if(!(todo_id > 0 && todo_id <= todos.size())) {
		std::cout<<"\nNo todo with that ID exists!\n"<<std::endl;
	} else {
		char selection;
		while(selection != 'Q' && selection != 'q') {
			clear_input();
			Todo* selected_todo = &todos[todo_id - 1];
			std::vector<std::string> menu_items {"C - change description", (*selected_todo).get_status() ? "X - incomplete" : "X - Complete", "Q - return to main menu"};
			std::cout<<'\n';
			header("UPDATE TODO");
			display_todo((*selected_todo), todo_id);
			display_menu(menu_items);
			std::cout<<"\nSelect an option from the options above: ";
			std::cin>>selection;

			switch (selection) {
				case 'X':
				case 'x': {
					(*selected_todo).change_status();
					break;
				}
				case 'Q':
				case 'q': {
					return; //return to main menu
					break;
				}
				default: {
					std::cout<<"\nUpdate Todo: **Not a valid option!**\n"<<std::endl;
					break;
				}
			}
		};
	}
}

void delete_todo(std::vector<Todo> &todos) {
	unsigned int todo_id;
	std::cout<<"Please enter ID of the todo you want to delete: ";
	if(!(std::cin>>todo_id)) {
		std::cin.clear();
		std::cout<<"\nPlease enter a valid ID!\n"<<std::endl;
	} else if(!(todo_id > 0 && todo_id <= todos.size())) {
		std::cout<<"\nNo todo with that ID exists!\n"<<std::endl;
	} else {
		clear_input();
		char confirmation;
		std::cout<<"Delete todo (ID: "<<todo_id<<"). Are you sure? (Y/N): ";
		std::cin>>confirmation;
		if(confirmation != 'Y' && confirmation != 'y') {
			std::cout<<"Todo not deleted."<<std::endl;
		} else {
			todos.erase(todos.begin() + todo_id - 1);
			std::cout<<"Todo deleted."<<std::endl;
		}
	}
	clear_input();
}

int main() {
	//Sample todos
	Todo todo1 {"create todo app"};
	Todo todo2 {"learn C++"};
	Todo todo3 {"get a programming job"};

	std::vector<Todo> todos {todo1, todo2, todo3};

	std::vector<std::string> menu_items {"C - create todo", "U - update todo", "D - delete todo", "Q - quit"};

	char selection;

	while(selection != 'q' && selection != 'Q') {
		header("TODOS");
		display_todos(todos);
		display_menu(menu_items);
		std::cout<<"\nSelect an option from the options above: ";
		std::cin>>selection;
		std::cout<<std::endl;
		clear_input();

		switch (selection) {
			case 'C': 
			case 'c': {
				create_todo(todos);
				break;
			}
			case 'U': 
			case 'u': {
				update_todo(todos);
				break;
			}
			case 'D': 
			case 'd': {
				delete_todo(todos);
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