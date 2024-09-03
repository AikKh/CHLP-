#include "h/Environment.h"

int main()
{
    Doer::Enviroment env;
    return env.Run("tests/fibonacci_with_keywords.dr");
}