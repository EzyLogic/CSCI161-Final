#include "Narrator.hpp"

const std::string Narrator::filename = "src/story/story.txt";

int Narrator::current_chapter = 0;

std::string Narrator::press_N = std::string(">>> press any key to continue <<<");

// Dialogue is designed to deallocate each of these as they are used.
//   To reuse, just make sure you pass a copy of the chapter into a Dialogue.
std::string* Narrator::story = new std::string[Narrator::MAX_CHAPTERS];

Narrator::Narrator()
{
    std::ifstream in(filename);
    std::string word;
    for(int i = 0; i < MAX_CHAPTERS; ++i) {
        in >> word;
        story[i] = std::string(word);
        story[i].append(" ");
        do {
            in >> word;
            if(word.compare("#") != 0 && !in.eof()) story[i].append(word + " ");
        } while(word.compare("#") != 0 && !in.eof());
    }
    return;
}

std::vector<std::string>& Narrator::split(std::string paragraph)
{
    std::stringstream in(paragraph);
    int k = 0;
    std::vector<std::string> *copy = new std::vector<std::string>();

    int total_length = 0;
    std::string word;
    in >> word;
    total_length += word.length();
    copy->push_back(word);

    while(!in.eof()) {
        while(1) {
            if((in >> word).eof()) break;
            if(copy->at(k).length() + word.length() + 1 > (size_t)MAX_LINE_WIDTH) break;

            copy->at(k).append(" " + word);
            total_length += word.length() + 1;
        }
        k++;
        copy->push_back(std::string(""));
        if(!in.eof()) copy->at(k).append(word);
        total_length = 0 + word.length();
    }
    copy->push_back(std::string(press_N));

    current_chapter++;

    return *copy;
}

std::vector<std::string> Narrator::narrate()
{
    return split( story[current_chapter] );
}
