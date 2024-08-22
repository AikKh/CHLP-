#pragma once

#include "Lexer.h"
#include "Parser.h"
#include "Interpretation/ActionTreeGenerator.h"

namespace Doer {

    class Enviroment {
    public:

        // TODO: Open stack after action tree is generated 
        Enviroment() : _stack{ StackFrame::Open() } {}

        ~Enviroment() {
            StackFrame::Close(_stack);
        }

        int Run(const string& filename) {
            //ObjectManager::InitializeOperations();

            // Opening
            string content = ReadFileIntoString(filename);

            // Lexical analysis
            Lexer lexer;
            vector<Token> tokens;

            cout << content << endl;
            cout << string(100, '-') << endl;

            lexer.LexCode(content, tokens);

            for (auto& token : tokens) {
                cout << token.ToString();
            }

            cout << endl;

            // Parsing
            Parser parser(tokens);
            CompoundNode* root = parser.Parse();

            // TODO: Memory shit is happating
            if (parser.Done()) {
                cout << "Parsed successfully" << endl;

                root->Print();
            }
            else {
                error.Report("Parser error", ErrorPriority::SOURCE_ERROR);
            }

            if (!error.IsOk()) {
                delete root;
                error.PrintErrors();
                return 1;
            }

            cout << "Valid code" << endl;
            /*cout << "Generating action tree..." << endl;

            Validator validator;
            ActionTreeGenerator generator{ *_stack, validator };
            ActionNode* action_tree = generator.Visit(root);

            if (!error.IsOk()) {
                delete root;
                delete action_tree;

                cout << "Failed to generate action tree" << endl;
                error.PrintErrors();
                return 1;
            }

            cout << "Running code" << endl;

            Object result = action_tree->Execute();

            if (!error.IsOk()) {
                delete root;
                delete action_tree;

                cout << "Failed to execute" << endl;
                error.PrintErrors();
                return 1;
            }

            cout << "======================== Stack Frame ========================" << endl;

            _stack->Print();

            cout << "=============================================================" << endl;*/

            delete root;
            //delete action_tree;
            return 0;
        }

    private:
        static string ReadFileIntoString(const string& filename) {
            std::ifstream file(filename);

            if (file.is_open()) {
                string content((std::istreambuf_iterator<char>(file)),
                    (std::istreambuf_iterator<char>()));

                // Close the file
                file.close();

                return content;
            }
            std::cerr << "Unable to open file: " << filename << endl;
            return "";
        }

    private:
        StackFrame* _stack = nullptr;
    };
}