#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>

class Todo {
	std::string description;
	bool completed {false};

	public:
		Todo(std::string description): description {description} {}
		std::string get_todo() const {
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

void display_linebreak(unsigned int DISPLAY_WIDTH) {
	std::cout<<std::setw(DISPLAY_WIDTH)<<std::setfill('-')<<""<<std::endl<<std::setfill(' ');
}

void header(unsigned int DISPLAY_WIDTH, void (*display_linebreak)(unsigned int)) {
	const std::string HEADING {"TODOS"};
	const auto HEADING_WIDTH {(DISPLAY_WIDTH/2)+(HEADING.length()/2)};
	std::cout<<std::setw(HEADING_WIDTH)<<HEADING<<std::endl;
	display_linebreak(DISPLAY_WIDTH);
}

void display_todos(std::vector<Todo> const &todos, unsigned int DISPLAY_WIDTH) {
	const unsigned int COLUMN_BUFFER {3}; //For separation between Todo table columns
	const unsigned int TODO_ID_COLUMN_WIDTH {3 + COLUMN_BUFFER}; //3 because assumming max todo id will be 3 digits e.g. 999
	const unsigned int STATUS_COLUMN_WIDTH {10 + COLUMN_BUFFER}; //10 because 'incomplete' is 10 chars long. 'complete' has 8 chars
	const unsigned int TODO_COLUMN_WIDTH {DISPLAY_WIDTH - TODO_ID_COLUMN_WIDTH - STATUS_COLUMN_WIDTH};
	const std::string strikethrough_start{"\e[9m"};
	const std::string strikethrough_stop{"\e[29m"};
	for(size_t i {0}; i < todos.size(); ++i) {
		const auto TODO_DESCRIPTION_WIDTH {todos[i].get_todo().length()};

		std::cout<<std::left<<std::setw(TODO_ID_COLUMN_WIDTH)<<i+1
		<<(todos[i].get_status() ? strikethrough_start : "")<<std::setw(TODO_DESCRIPTION_WIDTH)<<todos[i].get_todo()<<(todos[i].get_status() ? strikethrough_stop : "")
		<<std::setw(TODO_COLUMN_WIDTH - TODO_DESCRIPTION_WIDTH)<<""
		<<std::right<<std::setw(STATUS_COLUMN_WIDTH)<<(todos[i].get_status() ? "complete" : "incomplete")<<std::endl;
	}
}

void display_menu(std::vector<std::string> menu_items, int DISPLAY_WIDTH) {
	std::cout<<std::setw(DISPLAY_WIDTH)<<std::setfill('-')<<""<<std::endl<<std::setfill(' ');
	for(auto item:menu_items)
		std::cout<<item<<std::endl;
}

void create_todo(std::vector<Todo> &todos) {
	std::string description;
	std::cout<<"Enter the todo: ";
	std::getline(std::cin, description);
	Todo todo {description};
	todos.push_back(todo);
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
	Todo todo1 {"create todo app"};
	Todo todo2 {"learn C++"};
	Todo todo3 {"get a programming job"};

	std::vector<Todo> todos {todo1, todo2, todo3};

	std::vector<std::string> menu_items {"C - create todo", "U - update todo", "D - delete todo", "Q - quit"};

	const unsigned int DISPLAY_WIDTH {50};
	char selection;

	while(selection != 'q' && selection != 'Q') {
		header(DISPLAY_WIDTH, &display_linebreak);
		display_todos(todos, DISPLAY_WIDTH);
		display_menu(menu_items, DISPLAY_WIDTH);
		std::cout<<"\nSelect an option from the options above: ";
		std::cin>>selection;
		clear_input();

		switch (selection) {
			case 'C': 
			case 'c': {
				create_todo(todos);
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
				std::cout<<"\n**Not a valid option!**\n"<<std::endl;
			}
		}
	};

	return 0;
}