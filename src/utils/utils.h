#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <array>
#include <fstream>

#include "../globals.h"
#include "../classes/todo/todo.h"
#include "../classes/exceptions/file_exception.h"

//Util for console UI alignment, not a feature of the app
void ruler(unsigned int length);

//Clears the input buffer
void clear_input();

void display_linebreak();

void header(const std::string &HEADING);

template <size_t N>
void display_menu(const std::array<std::string, N> &menu_items) 
{
	display_linebreak();
	for(const auto &item:menu_items)
		std::cout<<item<<std::endl;
}

template <typename file_type>
void format_todo_data
(
	file_type &file, 
	const size_t &id, 
	const bool &status, 
	const std::string &description) 
{
	file<<id<<' '<<status<<' '<<description<<'\n';
}

void modify_todo_in_file_storage(char mode, std::fstream &file, size_t todo_id, std::string filename, std::string tempfile_path, Todo* selected_todo = nullptr);

#endif