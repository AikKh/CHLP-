#include "../h/Lexer.h"

void Lexer::SetUp()
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
    _currColumn = 1;
}

Lexer::Type Lexer::GetType(char c)
{
    auto type = charToType.find(c);
    if (type != charToType.end()) {
        return type->second;
    }
    return UNKNOWN;
}

void Lexer::LexCode(const string& code, vector<Token>& tokens)
{
    int prevIndex = 0;
    bool inComment = false;

    if (!_hasSetUp)
        SetUp();


    for (int i = 0; i < code.size(); ++i) {
        prevIndex = i;
        Type currType = GetType(code[i]);
        Token token(Token::Type::UNKNOWN, "");
        
        
        switch (currType)
        {
        case LETTER:
            token = HandleLetter(code, i);
            break;

        case WHITESPACE:
            HandleWhitespace(code, i);
            break;

        case OPERATOR:
            token = HandleOperator(code, i);
            break;

        case DIGIT:
            token = HandleDigit(code, i);
            break;
        
        case NEW_LINE:
            _currLine++;
            _currColumn = 0;
            inComment = false;

        case LINE_BREAK:
            if (!tokens.empty() && tokens.back().GetType() == Token::Type::LINE_END) {
                break;
            }
            if (!tokens.empty())
                token = MakeToken(Token::Type::LINE_END, ";");
            break;

        case COMMENT:
            inComment = true;
            break;

        default:
            cout << "Unknown symbol at " << i << endl;
            break;
        }

        _currColumn += (i - prevIndex + 1);

        if (!inComment && token.GetType() != Token::Type::UNKNOWN)
            tokens.push_back(token);
    }

    //if (tokens.back().GetType() == Token::Type::LINE_END) {
    //    //tokens.push_back(MakeToken(Token::Type::LINE_END, ";"));
    //    tokens.pop_back();
    //}
    if (tokens.back().GetType() != Token::Type::LINE_END)
        tokens.push_back(MakeToken(Token::Type::LINE_END, ";"));

    tokens.push_back(MakeToken(Token::Type::END_OF_FILE, std::to_string(EOF)));
}

Token Lexer::HandleLetter(const string& code, int& i) {
    bool hasDigit = false;

    int start = GoForwardWhile(code, i, 
        [&hasDigit](Type type) mutable
        {
            if (type == DIGIT){
                hasDigit = true;
            }

            return type == LETTER || type == DIGIT;
        }
    );

    Token::Type type = Token::Type::IDENTIFIER;
    string text = GetSub(code, start, i + 1);

    if (!hasDigit) {
        /// TODO:
        /// Check for keywords
        if (Keywords::IsKeyword(text)) {
            type = Token::Type::OPERATOR;
        }
    }
#ifndef NDEBUG
    //cout << text << endl;
#endif

    return MakeToken(type, text);
}

void Lexer::HandleWhitespace(const string& code, int& i) {
    GoForwardWhile(code, i, [](Type type) {
        return type == WHITESPACE;
    });
}

Token Lexer::HandleOperator(const string& code, int& i) {
    if (IsScope(code[i]))
        return MakeToken(Token::Type::SCOPE, string(1, code[i]));

    // TODO: refactore
    if (code[i] == '.')
        return HandleDigit(code, i);

    int start = GoForwardWhile(code, i, [&code, &i](Type type){
        return type == OPERATOR && !IsScope(code[i]);
    });

    string text = GetSub(code, start, i + 1);

    return MakeToken(Token::Type::OPERATOR, text);
}

Token Lexer::HandleDigit(const string& code, int& i) {
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
