#include "./todos.h"

bool Todos::load()
{
	namespace fs = std::filesystem;

	if(fs::exists(filename)) 
	{
		file.open(filename);

		if(!file)
			return false;

		size_t id;
		
		while(file>>id) 
		{
			std::string description;
			bool completed;

			std::getline(file>>std::ws, description, ',');
			file>>completed;
			file.ignore(); //ignore newline character

			Todo todo {id, description, completed};
			todos.push_back(todo);
		}

		file.close();
	} else {
		fs::create_directory("./data");

		file.open(filename, std::ios::out);

		if(!file)
			return false;

		file.close();
	}

	return true;
}

void Todos::display()
{
	if(todos.size() == 0) 
		std::cout<<"No Todos\n";
	else
		for(auto &todo:todos)
			todo.display();
}

bool Todos::create() 
{
	std::string description;
	std::cout<<"Enter the todo: ";
	std::getline(std::cin, description);

	file.open(filename, std::ofstream::app);

	if(!file)
		return false;

	size_t id = todos.size() + 1;

	file<<id<<' '<<description<<','<<0<<'\n';

	file.close();

	std::cout<<"\nNew todo added."<<std::endl;
	Todo todo {id, description};
	todos.push_back(todo);

	return true;
}

bool Todos::update() 
{
	std::string user_input;
	size_t todo_id;
	bool todo_original_status;
	std::string todo_original_description;
	bool initial = true;
	bool todo_picked = false;
	
	std::cout<<"Please enter the ID of the todo you want to update or enter q to quit: ";
	std::getline(std::cin, user_input);
	std::istringstream iss(user_input);
	iss>>todo_id;

	Todo* selected_todo;

	while(user_input != "q" && user_input != "Q") 
	{
		if(!iss>>todo_id)
		{
			std::cin.clear();
			std::cout<<"\nPlease enter a valid ID or enter q to quit: ";
			std::getline(std::cin, user_input);
		} 
		else if(!(todo_id > 0 && todo_id <= todos.size()))
		{
			std::cout<<"\nNo todo with that ID exists!";
			std::cout<<"\n\nPlease enter a valid ID or enter q to quit: ";
			std::getline(std::cin, user_input);
		} 
		else 
		{
			char selection;		
			selected_todo = &todos[todo_id - 1];

			if(initial) 
			{
				todo_original_status = selected_todo->get_status();
				todo_original_description = selected_todo->get_description();
				initial = false;
				todo_picked = true;
			}

			std::vector<std::string> menu_items {"C - change description", selected_todo->get_status() ? "X - incomplete" : "X - complete", 
				(selected_todo->get_description() != todo_original_description 
					|| selected_todo->get_status() != todo_original_status) ? "Q - Save changes and return to main menu" : "Q - return to main menu"};

			std::cout<<'\n';
			header("UPDATE TODO");
			selected_todo->display();
			display_menu(menu_items);
			std::cout<<"\nSelect an option from the options above: ";
			std::cin>>selection;

			switch (selection) 
			{
				case 'C':
				case 'c': 
				{
					std::string new_description;
					clear_input();
					std::cout<<"\nPlease enter the new description: ";
					std::getline(std::cin, new_description);
					selected_todo->change_description(new_description);
					std::cout<<"\nTodo description changed."<<std::endl;
					break;
				}
				case 'X':
				case 'x':
				{
					selected_todo->change_status();
					std::cout<<"\nTodo status changed."<<std::endl;
					break;
				}
				case 'Q':
				case 'q': 
				{
					user_input = selection; //to exit loop
					break;
				}
				default: 
				{
					clear_input();
					std::cout<<"\nUpdate Todo: **Not a valid option!**"<<std::endl;
					break;
				}
			}
		};
	}
	
	if(todo_picked) {
		if(selected_todo->get_status() != todo_original_status 
			|| selected_todo->get_description() != todo_original_description) 
		{
			file.open(filename, std::ifstream::in);

			std::ofstream temp_file;
			temp_file.open(tempfile_path);

			if(!file || !temp_file)
				return false;

			std::string line;
			size_t file_todo_id;

			while(file>>file_todo_id)
			{
				if(file_todo_id != todo_id)
				{
					std::getline(file, line);
					temp_file<<file_todo_id<<line<<'\n';
				}
				else
				{
					temp_file<<file_todo_id<<' '<<selected_todo->get_description()<<','<<selected_todo->get_status()<<'\n';
				}
			}

			file.close();
			temp_file.close();

			std::remove(filename.c_str());
			std::rename(tempfile_path.c_str(), filename.c_str());
		}
	}
	std::cout<<"\nReturning to main menu..."<<std::endl;
	return true;
}

bool Todos::del() {
	size_t todo_id;
	std::cout<<"Please enter ID of the todo you want to delete: ";

	if(!(std::cin>>todo_id)) 
	{
		std::cin.clear();
		std::cout<<"\nPlease enter a valid ID!\n"<<std::endl;
	} 
	else if(!(todo_id > 0 && todo_id <= todos.size())) 
	{
		std::cout<<"\nNo todo with that ID exists!\n"<<std::endl;
	} 
	else 
	{
		char confirmation;
		clear_input();
		std::cout<<"\nDelete todo (ID: "<<todo_id<<"). Are you sure? (Y/N): ";
		std::cin>>confirmation;
		if(confirmation != 'Y' && confirmation != 'y') 
		{
			std::cout<<"\nTodo not deleted."<<std::endl;
		} 
		else 
		{
			file.open(filename, std::ifstream::in);
			std::ofstream temp_file;
			temp_file.open(tempfile_path);

			if(!file || !temp_file)
				return false;

			std::string line;
			size_t file_todo_id;
			size_t i {1};

			while(file>>file_todo_id) 
			{
				std::getline(file, line);
				if(todo_id != file_todo_id) 
				{
					temp_file<<i<<line<<'\n';
					++i;
				}
			}
			
			file.close();
			temp_file.close();

			std::remove(filename.c_str());
			std::rename(tempfile_path.c_str(), filename.c_str());

			todos.erase(todos.begin() + todo_id - 1);

			for(size_t i {0}; i < todos.size(); ++i) 
			{
				todos[i].change_id(i + 1);
			}

			std::cout<<"\nTodo deleted."<<std::endl;
		}
	}
	clear_input();
	
	return true;
}