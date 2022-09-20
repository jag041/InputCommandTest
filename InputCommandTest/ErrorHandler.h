#pragma once
#include <string>


class ErrorHandler {
public:
	ErrorHandler(std::string msg) : message(msg) {
	}

	std::string what() const
	{
		return message;
	}

private:
	std::string message;
};
