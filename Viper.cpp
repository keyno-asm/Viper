#include "./lib/Algs.h"
#include "./lib/CodeAnalys.h"
#include<iostream>

int main()
{
    STRVEC code = {"print(\"Hello world\")", "input(uInput)", "print(uInput, foo, dog)"};

    STRVEC uwu = Tokenize(code);

    for (STR line : uwu)
    {
        std::cout << line << "\n";
    }
}