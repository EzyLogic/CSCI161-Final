#pragma once

#include <string>
#include <exception>

class MessageWidthException : public std::exception
{

	std::string error_message;
	std::string *data;
	int N;

public:

	MessageWidthException(std::string &&error_message, std::string *message, int n)
	{
		this->error_message = std::move(error_message);
		N = n;
		data = new std::string[n];
		for (int i = 0; i < n; i++)
			data[i] = std::string(message[i]);
	}

	~MessageWidthException() {
		delete [] data;
	}

	const char* what() const noexcept
	{
		return error_message.c_str();
	}

	std::string *get_message()
	{ return data; }

	int get_no_lines()
	{ return N; }
	
};
