#include "h/Environment.h"

int main()
{
    Doer::Enviroment env;
    auto res = env.Run("tests/fibonacci_with_keywords.dr");

    return res;
}