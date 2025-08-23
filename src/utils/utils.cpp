#include "./utils.h"

//Util for console UI alignment, not a feature of the app
void ruler(unsigned int length) 
{
	std::string digits {"1234567890"};
	for(size_t i {0}; i < length; ++i)
		std::cout<<digits;
	std::cout<<std::endl;
}

//Clears the input buffer
void clear_input() 
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void display_linebreak() 
{
	std::cout<<std::setw(DISPLAY_WIDTH)<<std::setfill('-')<<""<<std::endl<<std::setfill(' ');
}

void header(const std::string HEADING) 
{
	const auto HEADING_WIDTH {(DISPLAY_WIDTH/2)+(HEADING.length()/2)};
	std::cout<<std::setw(HEADING_WIDTH)<<HEADING<<std::endl;
	display_linebreak();
}

void display_menu(std::vector<std::string> menu_items) 
{
	display_linebreak();
	for(auto item:menu_items)
		std::cout<<item<<std::endl;
}

void modify_todo_in_file_storage
(
	char mode, 
	std::fstream &file, 
	std::ofstream &temp_file, 
	size_t todo_id, std::string filename, 
	std::string tempfile_path, 
	Todo* selected_todo
)  
{
	size_t file_todo_id;
	size_t new_file_id {1};

	while(file>>file_todo_id) 
	{
		bool status;
		file>>status;

		std::string description;
		std::getline(file>>std::ws, description);

		switch (mode)
		{
			case 'u':
			{
				if(file_todo_id != todo_id)
					format_todo_data(temp_file, file_todo_id, status, description);
				else
					format_todo_data(temp_file, file_todo_id, selected_todo->get_status(), selected_todo->get_description());
				break;
			}
			case 'd':
			{
				if(todo_id != file_todo_id) 
				{
					format_todo_data(temp_file, new_file_id, status, description);
					++new_file_id;
				}
			}
			default:
				break;
		}
	}
	
	file.close();
	temp_file.close();

	std::remove(filename.c_str());
	std::rename(tempfile_path.c_str(), filename.c_str());
}