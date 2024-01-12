#include "../h/ErrorHandler.h"

ErrorHandler error;

void ErrorHandler::Report(string message, ErrorPriority priority, Token* token)
{
	string error = GetErrorMessage(message, priority);

	if (token) {
		error += " " + token->ToString();
	}
	AddError(error);
}

void ErrorHandler::ReportAt(string message, ErrorPriority priority, int line, int column)
{
	string error = GetErrorMessage(message, priority);
	error += " at " + std::to_string(line) + ':' + std::to_string(column);
	AddError(error);
}

void ErrorHandler::PrintErrors()
{
	for (auto err : _errors) {
		cout << err << endl;
	}
}
