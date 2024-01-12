#include "../h/Token.h"

Token::Token(Type type, string text, int line, int column)
{
	_type = type;
	_text = text;
	this->Line = line;
	this->Column = column;
}

string Token::ToString() const
{
	int distance = 12;
	int textTistance = std::max(int(_text.size() + 2), distance);
	string type = TypeToString(_type);

	return "Type: " + type + string(distance - type.size(), ' ') + 
		   "Text: \"" + _text + "\"" + string(textTistance - _text.size(), ' ') +
		   "Size: " + std::to_string(_text.size()) + string(distance - (int)log10(Line + 1), ' ') +
		   "Line: " + std::to_string(Line) + string(distance - (int)log10(Column + 1), ' ') +
		   "Column: " + std::to_string(Column) + "\n";
}

