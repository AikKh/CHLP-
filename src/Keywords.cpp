#include "../h/Keywords.h"

bool Keywords::IsKeyword(const string& str) {
    for (const auto& op : keywords) {
        if (op == str)
            return true;
    }
    return false;
}

const vector<string> Keywords::keywords = {
    "not",
    "and",
    "or",
    "true",
    "false",
};
    /*"*",
    "/",
    "%",
    "+",
    "-",
    "<",
    "<=",
    ">",
    ">=",
    "==",
    "!=",
    "=",
    ","*/