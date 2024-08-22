#include "../h/Token.h"

namespace Doer {

	Doer::Token::Token(Type type, string text, int line, int column)
	{
		_type = type;
		_text = text;

		Line = line;
		Column = column;
	}

	Token::Token(const Token& other) :
		_type{ other._type }, _text{ other._text }, Line{ other.Line }, Column{ other.Column }
	{}

	Token::Token(Token&& other) noexcept :
		_type{ other._type }, _text { move(other._text) }, Line{ other.Line }, Column { other.Column }
	{}

	Token& Token::operator=(const Token& other)
	{
		if (this == &other) return *this;

		_type = other._type;
		_text = other._text;

		Line = other.Line;
		Column = other.Column;

		return *this;
	}

	Token& Token::operator=(Token&& other) noexcept
	{
		if (this == &other) return *this;

		_type = other._type;
		_text = move(other._text);

		Line = other.Line;
		Column = other.Column;

		return *this;
	}

	string Doer::Token::ToString() const
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
}