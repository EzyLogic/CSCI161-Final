#pragma once

#include <string>
#include <vector>
#include <exception>

class MessageHeightException : public std::exception
{

	std::string error_message;
	std::vector<std::string> data;

public:

	MessageHeightException(std::string &&error_message, std::vector<std::string> message)
	{
		this->error_message = std::move(error_message);
		data = std::vector<std::string>(message);
	}

	~MessageHeightException() {}

	const char* what() const noexcept
	{
		return error_message.c_str();
	}

	std::vector<std::string> get_message()
	{ return data; }
	
};
