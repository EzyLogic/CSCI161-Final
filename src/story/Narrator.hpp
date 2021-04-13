#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

class Narrator 
{

	static int current_chapter;

	static const std::string filename;
	static const int MAX_LINE_WIDTH = 55;
	static const int MAX_CHAPTERS = 3;	
	static std::string* story;
	
	static std::string press_N;

    std::vector<std::string>& split(std::string);

public:

	Narrator();

	std::vector<std::string> narrate();

};
