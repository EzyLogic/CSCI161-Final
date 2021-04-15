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

	static const std::string humanFilename;
    static const std::string elfFilename;
	static const int MAX_LINE_WIDTH = 55;
	static const int MAX_CHAPTERS = 2;
	static std::string* story;
	
	static std::string press_N;

    std::vector<std::string>& split(std::string);

public:

	Narrator(char);

	std::vector<std::string> narrate();
	bool theEnd();

};
