#ifndef _GLOBALS_
#define _GLOBALS_

#include <string>

//Program constants
const unsigned int DISPLAY_WIDTH {50};
const unsigned int COLUMN_BUFFER {3}; //For separation between Todo table columns
const unsigned int TODO_ID_COLUMN_WIDTH {3 + COLUMN_BUFFER}; //3 because assumming max todo id will be 3 digits e.g. 999
const unsigned int STATUS_COLUMN_WIDTH {10 + COLUMN_BUFFER}; //10 because 'incomplete' is 10 chars long. 'complete' has 8 chars
const unsigned int TODO_COLUMN_WIDTH {DISPLAY_WIDTH - TODO_ID_COLUMN_WIDTH - STATUS_COLUMN_WIDTH};
const std::string strikethrough_start{"\033[9m"};
const std::string strikethrough_stop{"\033[29m"};

#endif