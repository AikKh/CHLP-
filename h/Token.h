#pragma once

#include "Keywords.h"

struct Token {
public:
	enum Type // Non-Terminals
	{
		WHITESPACE,
		LITERAL,
		IDENTIFIER,
		OPERATOR,
		KEYWORD,
		SCOPE, // Is also operator basically
		LINE_END,
		END_OF_FILE,
		UNKNOWN,
	};

	Token(Type, string, int line = 0, int column = 0);
	std::string ToString() const;

	bool operator==(const Token& other) const {
		return this->_type == other._type && this->_text == other._text;
	}

	bool operator!=(const Token& other) const {
		return !(*this == other);
	}

	const Type& GetType() const {
		return _type;
	}

	const string& GetText() const {
		return _text;
	}

	int Line;
	int Column;

private:
	Type _type;
	string _text;


	static string TypeToString(Type type) {
		switch (type)
		{
		case Token::WHITESPACE:
			return "WHITESPACE";
		case Token::LITERAL:
			return "LITERAL";
		case Token::IDENTIFIER:
			return "IDENTIFIER";
		case Token::OPERATOR:
			return "OPERATOR";
		case Token::KEYWORD:
			return "KEYWORD";
		case Token::SCOPE:
			return "SCOPE";
		case Token::LINE_END:
			return "LINE_END";
		case Token::END_OF_FILE:
			return "END_OF_FILE";
		case Token::UNKNOWN:
			return "UNKNOWN";
		default:
			break;
		}
	}

	// friend class Node;
};