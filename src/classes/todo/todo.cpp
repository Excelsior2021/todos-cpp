#include "todo.h"

Todo::Todo(size_t id, std::string description, bool completed): 
	id {id}, description {description}, completed{completed} {}

void Todo::display() const 
{
	const auto TODO_DESCRIPTION_WIDTH {description.length()};
	
	std::cout<<std::left<<std::setw(TODO_ID_COLUMN_WIDTH)<<id
	<<(completed ? strikethrough_start : "")<<std::setw(TODO_DESCRIPTION_WIDTH)<<description<<(completed ? strikethrough_stop : "")
	<<std::setw(TODO_COLUMN_WIDTH - TODO_DESCRIPTION_WIDTH)<<""
	<<std::right<<std::setw(STATUS_COLUMN_WIDTH)<<(completed ? "complete" : "incomplete")<<std::endl;
}

size_t Todo::get_id() const 
{
	return id;
}

std::string Todo::get_description() const
{
	return description;
}

bool Todo::get_status() const
{
	return completed;
}

void Todo::change_id(const size_t &new_id)
{
	id = new_id;
}

void Todo::change_description(const std::string &new_description)
{
	description = new_description;
}

void Todo::change_status()
{
	completed = !completed;
}