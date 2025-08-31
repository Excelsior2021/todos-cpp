#include "./todos.h"

void Todos::load()
{
	namespace fs = std::filesystem;

	if(fs::exists(filename)) 
	{
		file.open(filename);

		if(!file)
			throw FileException{};

		size_t id;
		
		while(file>>id) 
		{
			bool status;
			file>>status;

			std::string description;
			std::getline(file>>std::ws, description);

			todos.emplace_back(id, description, status);
		}

		file.close();
	} 
	else 
	{
		fs::create_directory("./data");

		file.open(filename, std::ios::out);

		if(!file)
			throw FileException{};

		file.close();
	}
}

void Todos::display()
{
	if(todos.empty()) 
		std::cout<<"No Todos\n";
	else
		for(auto &todo:todos)
			todo.display();
}

void Todos::create() 
{
	std::string user_input;
	std::cout<<"Enter the todo or enter q to quit: ";
	std::getline(std::cin, user_input);

	if(user_input == "Q" || user_input == "q")
		std::cout<<"\nReturning to main menu..."<<std::endl;

	std::string description = user_input;

	file.open(filename, std::ofstream::app);

	if(!file)
		throw FileException{};

	size_t id {todos.size() + 1};
	bool status {false};

	format_todo_data(file, id, status, description);

	file.close();

	todos.emplace_back(id, description);

	std::cout<<"\nNew todo added."<<std::endl;
}

void Todos::update() 
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
		if(!todo_id)
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

			//for indexed based IDs
			selected_todo = &todos.at(todo_id - 1);

			// //for non-indexed based IDs
			// selected_todo = &(*std::find_if(todos.begin(), todos.end(), 
			// 	[todo_id](const Todo &todo)
			// 	{ 
			// 		return todo.get_id() == todo_id; 
			// 	}
			// ));


			if(initial) 
			{
				todo_original_status = selected_todo->get_status();
				todo_original_description = selected_todo->get_description();
				initial = false;
				todo_picked = true;
			}

			std::array<std::string, 3> menu_items {"C - change description", selected_todo->get_status() ? "X - incomplete" : "X - complete", 
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
	
	if(todo_picked) 
	{
		if
		(
			selected_todo->get_status() != todo_original_status 
			|| selected_todo->get_description() != todo_original_description
		) 
			modify_todo_in_file_storage
			(
				'u',
				file,
				todo_id,
				filename,
				tempfile_path,
				selected_todo
			);
	}

	std::cout<<"\nReturning to main menu..."<<std::endl;
}

void Todos::del() {
	std::string user_input;
	size_t todo_id;

	std::cout<<"Please enter ID of the todo you want to delete or enter q to quit: ";
	std::getline(std::cin, user_input);

	std::istringstream iss(user_input);
	iss>>todo_id;

	if(user_input == "Q" || user_input == "q")
		std::cout<<"\nReturning to main menu..."<<std::endl;
	else if(!todo_id) 
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
		std::cout<<"\nDelete todo (ID: "<<todo_id<<"). Are you sure? (Y/N): ";
		std::cin>>confirmation;
		
		if(confirmation != 'Y' && confirmation != 'y') 
		{
			std::cout<<"\nTodo not deleted."<<std::endl;
		} 
		else 
		{
			modify_todo_in_file_storage
			(
				'd',
				file,
				todo_id,
				filename,
				tempfile_path
			);

			//remove deleted todo from todos vector
			todos.erase(todos.begin() + todo_id - 1);

			//update the ids of remaining todos
			for(size_t i {0}; i < todos.size(); ++i) 
			{
				todos[i].change_id(i + 1);
			}

			std::cout<<"\nTodo deleted."<<std::endl;
		}
	}
	clear_input();
}