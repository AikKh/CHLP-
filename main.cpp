#include "h/Lexer.h"
#include "h/Parser.h"

string readFileIntoString(const string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        string content((std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>()));

        // Close the file
        file.close();

        return content;
    }
    else {
        std::cerr << "Unable to open file: " << filename << endl;
        return "";
    }
}

//void PrintAst(Node* node, int level = 0) {
//    if (node) {
//        cout << string(level, ' ') << node->GetValue().GetText() << endl;
//        PrintAst(node->GetLeft(), level + 2);
//        PrintAst(node->GetRight(), level + 2);
//    }
//}

int main()
{
    // Opening
    string filename = "tests/ParserTest.dr";
    //string filename = "tests/lexerTest.dr";
    string content = readFileIntoString(filename);

    // Lexical analysis
    Lexer lexer;
    vector<Token> tokens;

    cout << content << endl;

    lexer.LexCode(content, tokens);

    for (auto& token : tokens) {
        cout << token.ToString();
    }

    cout << endl;

    // Parsing
    Parser parser(tokens);
    Node* root = parser.Parse();

    // TODO: Memory shit is happating
    if (parser.Done()) {
        cout << "Parsed successfully" << endl;

        root->Print();

        delete root;
    }
    else {
        error.Report("Parser error", ErrorPriority::SOURCE_ERROR);
    }

    // Final
    if (error.IsOk()) {
        cout << "Valid code" << endl;
        return 0;
    }

    error.PrintErrors();
    return 1;
}