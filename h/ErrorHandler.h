#pragma once

#include "Token.h"

enum ErrorPriority
{
	SOURCE_ERROR,
	RUNTIME_ERROR
};


class ErrorHandler {
public:

	void Report(string message, ErrorPriority priority, Token* token = nullptr);

	void ReportAt(string message, ErrorPriority priority, int line, int column);

	void PrintErrors();

	bool IsOk() const { return !_hasError; }

private:

	bool _hasError = false;
	vector<string> _errors;

	void AddError(string error) {
		_hasError = true;
		_errors.push_back(error);
	}

	static string ErrorPriorityToString(ErrorPriority priority) {
		switch (priority)
		{
		case SOURCE_ERROR:
			return "Source error";
		case RUNTIME_ERROR:
			return "Runtime error";
		default:
			return "Unknown error";
		}
	}

	static string GetErrorMessage(string message, ErrorPriority priority) {
		return ErrorPriorityToString(priority) + ": " + message;
	}
};

// Global error object (in source)
extern ErrorHandler error;
