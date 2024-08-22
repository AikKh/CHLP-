#pragma once

#include "Includes.h"

namespace Doer {

	struct Token {
	public:
		enum Type // Non-Terminals
		{
			WHITESPACE,
			LITERAL,
			IDENTIFIER,
			OPERATOR,
			KEYWORD,
			SCOPE,
			COMMA,
			LINE_END,
			END_OF_FILE,
			UNKNOWN,
		};

		Token(Type, string, int line = 0, int column = 0);

		Token(const Token& other);

		Token(Token&& other) noexcept;

		Token& operator=(const Token&);

		Token& operator=(Token&&) noexcept;

		std::string ToString() const;

		bool Equals(Type type, string text) const {
			return _type == type && _text == text;
		}

		bool operator==(const Token& other) const {
			return _type == other._type && _text == other._text;
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

		static const Token Default() {
			return Token(Token::UNKNOWN, "");
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
			case Token::COMMA:
				return "COMMA";
			case Token::LINE_END:
				return "LINE_END";
			case Token::END_OF_FILE:
				return "END_OF_FILE";
			case Token::UNKNOWN:
			default:
				return "UNKNOWN";
			}
		}

		// friend class Node;
	};
}