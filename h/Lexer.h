#pragma once

#include "ErrorHandler.h"
#include "AllOperators.h"

namespace Doer {

	class Lexer {
	public:
		enum Type
		{
			WHITESPACE,
			DIGIT,
			LETTER,
			OPERATOR,
			LINE_BREAK,
			NEW_LINE,
			END_OF_FILE,
			COMMENT,
			UNKNOWN,
		};

		void LexCode(const string&, vector<Token>&);

	private:
		int _currLine = 0;
		int _currColumn = 0;

		bool _hasSetUp = false;
		unordered_map<char, Type> charToType;
		unordered_set<string> keywords;

		void SetUp();

		Type GetType(char);

		// Handlers

		Token HandleLetter(const string& code, int& i);

		void HandleWhitespace(const string& code, int& i);

		Token HandleOperator(const string& code, int& i);

		Token HandleDigit(const string& code, int& i);

		// Helper functions

		int GoForwardWhile(const string& code, int& i, function<bool(Type)> condition) {
			/// <summary>
			/// Goes forward while some condition and return the begining
			/// </summary>

			int start = i;

			Type nextType;

			do {
				nextType = GetType(code[++i]);
			} while (condition(nextType) && i < code.size());

			i--;
			return start;
		}

		Token MakeToken(Token::Type type, string str) {
			return Token(type, str, _currLine, _currColumn);
		}

		bool CheckFloatingPoint(char c, bool& hasPoint) const {
			// Can't repeat twice

			if (c == '.') {
				if (!hasPoint)
					return hasPoint = true;
				error.ReportAt("Invalid floating point", SOURCE_ERROR, _currLine, _currColumn);
			}
			return false;
		}

		inline void ShiftColumn(int start, int end) {
			_currColumn += (end - start + 1);
		}

		inline bool IsKeyword(const string& str) {
			return keywords.find(str) != keywords.end();
		}

		inline bool IsBoolean(const string& str) {
			return str == "true" || str == "false";
		}

		static bool IsScope(char c) {
			return c == '[' || c == '{' || c == '(' || c == ']' || c == '}' || c == ')';
		}

		static bool IsComma(char c) {
			return c == ',';
		}

		static string GetSub(const string& code, int start, int end) {
			return code.substr(start, end - start);
		}
	};
}