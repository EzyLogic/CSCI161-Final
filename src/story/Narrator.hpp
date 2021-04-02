#pragma once

#include <string>

class Narrator 
{

	static int current_chapter;

	static const int MAX_CHAPTERS = 3;	
	static const char*** story;
	static const int no_lines[MAX_CHAPTERS];
	
	static std::string press_N;

public:

	Narrator() {}

	const char** narrate();
	int get_no_lines();

	// writing a function to split up a string into an array of strings for you will save you a lot of work...

};
