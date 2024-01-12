#pragma once

#include "includes.h"

class Keywords {
public:
    static bool IsKeyword(const string&);

private:
    static const vector<string> keywords;
};
