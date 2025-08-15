#include "todo.h"

void Todo::display(size_t id) {
	const auto TODO_DESCRIPTION_WIDTH {description.length()};
	std::cout<<std::left<<std::setw(TODO_ID_COLUMN_WIDTH)<<id
	<<(completed ? strikethrough_start : "")<<std::setw(TODO_DESCRIPTION_WIDTH)<<description<<(completed ? strikethrough_stop : "")
	<<std::setw(TODO_COLUMN_WIDTH - TODO_DESCRIPTION_WIDTH)<<""
	<<std::right<<std::setw(STATUS_COLUMN_WIDTH)<<(completed ? "complete" : "incomplete")<<std::endl;
}