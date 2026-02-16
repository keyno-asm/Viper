#include "./lib/Algs.h"
#include "./lib/CodeAnalys.h"
#include<iostream>

int main()
{
    STRVEC code = { "input(art)","print(\"Hello world\")" };

    STRVEC uwu = Tokenize(code);

    STR line = OneInstTranslate(uwu);

    for (int i = 0; i < std::size(uwu); i++)
    {
        std::cout << uwu[i] << std::endl;
    }

    std::cout << line << std::endl;
}
