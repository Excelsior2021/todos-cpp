#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <vector>
#include <fstream>

#include "../globals.h"
#include "../classes/todo/todo.h"

//Util for console UI alignment, not a feature of the app
void ruler(unsigned int length);

//Clears the input buffer
void clear_input();

void display_linebreak();

void header(const std::string HEADING);

void display_menu(std::vector<std::string> menu_items);

void format_todo_data(std::fstream &file, size_t id, bool status, std::string description);
void format_todo_data(std::ofstream &file, size_t id, bool status, std::string description);

void modify_todo_in_file_storage(char mode, std::fstream &file, std::ofstream &temp_file, size_t todo_id, std::string filename, std::string tempfile_path, Todo* selected_todo = nullptr);

#endif