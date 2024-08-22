#include "../h/Lexer.h"

namespace Doer {

    void Doer::Lexer::SetUp()
    {
        for (char c = 'A'; c <= 'Z'; ++c)
            charToType[c] = LETTER;
        for (char c = 'a'; c <= 'z'; ++c)
            charToType[c] = LETTER;

        charToType['_'] = LETTER;

        for (char c = '0'; c <= '9'; ++c)
            charToType[c] = DIGIT;

        //charToType['.'] = OPERATOR;

        charToType['\n'] = NEW_LINE;

        charToType[';'] = LINE_BREAK;
        charToType[' '] = WHITESPACE;
        charToType['\t'] = WHITESPACE;
        charToType['\r'] = WHITESPACE;

        charToType['#'] = COMMENT;

#pragma region OperatorsRegion

        charToType['['] = OPERATOR;
        charToType['{'] = OPERATOR;
        charToType['('] = OPERATOR;

        charToType[']'] = OPERATOR;
        charToType['}'] = OPERATOR;
        charToType[')'] = OPERATOR;

        charToType['+'] = OPERATOR;
        charToType['-'] = OPERATOR;
        charToType['*'] = OPERATOR;
        charToType['/'] = OPERATOR;

        charToType['<'] = OPERATOR;
        charToType['>'] = OPERATOR;

        charToType['^'] = OPERATOR;

        charToType['!'] = OPERATOR;
        charToType['?'] = OPERATOR;

        charToType['='] = OPERATOR;

        charToType[','] = OPERATOR;

#pragma endregion

        charToType[-1] = END_OF_FILE;

        _hasSetUp = true;
        _currLine = 1;
        _currColumn = 0;
    }

    Doer::Lexer::Type Doer::Lexer::GetType(char c)
    {
        auto type = charToType.find(c);
        if (type != charToType.end()) {
            return type->second;
        }
        return UNKNOWN;
    }

    void Doer::Lexer::LexCode(const string& code, vector<Token>& tokens)
    {
        int prevIndex = 0;

        if (!_hasSetUp)
            SetUp();

        for (int i = 0; i < code.size(); ++i) {
            prevIndex = i;
            Type currType = GetType(code[i]);

            switch (currType)
            {
            case LETTER:
                tokens.push_back(HandleLetter(code, i));
                break;

            case WHITESPACE:
                HandleWhitespace(code, i);
                break;

            case OPERATOR:
                tokens.push_back(HandleOperator(code, i));
                break;

            case DIGIT:
                tokens.push_back(HandleDigit(code, i));
                break;

            case NEW_LINE:
                _currLine++;
                _currColumn = 0;
                break;

            case LINE_BREAK:
                if (tokens.empty() || tokens.back().GetType() == Token::LINE_END)
                    break;
                tokens.push_back(MakeToken(Token::Type::LINE_END, ";"));
                break;

            case COMMENT:
                GoForwardWhile(code, i, [](Type type) {
                    return type != NEW_LINE;
                    });
                break;

            default:
                error.ReportAt("Unknown symbol " + string(1, code[i]), ErrorPriority::SOURCE_ERROR, _currLine, _currColumn);
                break;
            }

            ShiftColumn(prevIndex, i);
        }

        //if (tokens.back().GetType() == Token::Type::LINE_END)
        //    tokens.pop_back();

        tokens.push_back(MakeToken(Token::Type::END_OF_FILE, std::to_string(EOF)));
    }

    Doer::Token Doer::Lexer::HandleLetter(const string& code, int& i) {
        bool hasDigit = false;

        int start = GoForwardWhile(code, i,
            [&hasDigit](Type type) mutable
            {
                if (type == DIGIT) {
                    hasDigit = true;
                }

                return type == LETTER || type == DIGIT;
            }
        );

        Token::Type type = Token::Type::IDENTIFIER;
        string text = GetSub(code, start, i + 1);

        if (!hasDigit && operators.IsOperator(text)) {
            /// Check for operators
            type = Token::Type::OPERATOR;
        }

        return MakeToken(type, text);
    }

    void Doer::Lexer::HandleWhitespace(const string& code, int& i) {
        GoForwardWhile(code, i, [](Type type) {
            return type == WHITESPACE;
            });
    }

    Doer::Token Doer::Lexer::HandleOperator(const string& code, int& i) {
        if (IsScope(code[i]))
            return MakeToken(Token::SCOPE, string(1, code[i]));
        else if (IsComma(code[i]))
            return MakeToken(Token::COMMA, string(1, code[i]));

        // TODO: refactore
        if (code[i] == '.')
            return HandleDigit(code, i);

        int start = GoForwardWhile(code, i, [&code, &i](Type type) {
            return type == OPERATOR && !IsScope(code[i]);
            });

        string text = GetSub(code, start, i + 1);

        return MakeToken(Token::Type::OPERATOR, text);
    }

    Doer::Token Doer::Lexer::HandleDigit(const string& code, int& i) {
        bool hasPoint = false;
        bool firstLetter = true;

        int start = GoForwardWhile(code, i, [this, &code, &i, &hasPoint](Type type) {
            if (type == LETTER) {
                //throw std::runtime_error("Invalid literal");
                error.ReportAt("Invalid literal", SOURCE_ERROR, _currLine, _currColumn);
            }

            // Floating point logic
            if (CheckFloatingPoint(code[i], hasPoint))
                return true;

            return type == DIGIT;
            });

        string text = GetSub(code, start, i + 1);

        return MakeToken(Token::Type::LITERAL, text);
    }
}