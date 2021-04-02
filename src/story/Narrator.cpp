#include "Narrator.hpp"

int Narrator::current_chapter = 0;

std::string Narrator::press_N = std::string(">>> press any key to continue <<<");

// you need to keep the number of lines matching for Narrator to work properly
const int Narrator::no_lines[]
	{ 6, 8, 3 };

// Dialogue is designed to deallocate each of these as they are used.
//   To reuse, just make sure you pass a copy of the chapter into a Dialogue.
const char*** Narrator::story = new const char**[Narrator::MAX_CHAPTERS]{
	/* intro */
	new const char*[no_lines[0]]{
		// ****************** max line length ******************/
		"A gigantic diamond-shaped flame is in the blue sky!",
		"It started as a speck, then quickly eclipsed the moon.",
		"Now it rivals the sun in brightness, and you wonder...",
		"...aliens? or some other phenomenon??",
		"",
		press_N.c_str()
	},
	/* Chapter 1 */
	new const char*[no_lines[1]]{
		// ****************** max line length ******************/
		"Is there shelter from impact of the flaming diamond?",
		"At left is a door to the offices you are on top of.",
		"At right is a fire escape.",
		"Below is a truck parked full of clothing donations.",
		"Helicopters fly low and one descends low enough so",
		"a stealth-suited marine can jump out safely.",
		"",
		press_N.c_str()
	},
	/* Chapter 2 */
	new const char*[no_lines[2]]{
		// ****************** max line length ******************/
		"Add more to your story!",
		"",
		press_N.c_str()
	}
};

const char** Narrator::narrate()
{ return story[current_chapter++]; }

int Narrator::get_no_lines()
{ return no_lines[current_chapter]; }
