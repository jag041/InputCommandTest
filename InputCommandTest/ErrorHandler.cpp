#include "ErrorHandler.h"

ErrorHandler::ErrorHandler(std::string msg) : message(msg) {
}

std::string ErrorHandler::what() const
{
	return message;
}
