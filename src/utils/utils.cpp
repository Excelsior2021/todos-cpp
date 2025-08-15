#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <vector>

#include "./utils.h"

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

void display_menu(std::vector<std::string> menu_items) {
	display_linebreak();
	for(auto item:menu_items)
		std::cout<<item<<std::endl;
}