#include "./lib/Algs.h"
#include "./lib/CodeAnalys.h"
#include<iostream>

int main()
{
    STRVEC code = { "double srg = 12 + rt",
        "int art = 10",
        "input(art)",
        "print(\"Hello world\" , art)", 
        "if(art == 10)", 
        "{", 
        "print(srg)", 
        "}"};

    STRVV uwu = Tokens(code);

    STRVEC a = TranslateCpp(uwu);
    
    std::cout << "\n**TOKENS**\n\n";

    for (int i = 0; i < std::size(uwu); i++)
    {
        for (int j = 0; j < std::size(uwu[i]); j++)
        {
            std::cout << uwu[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n**TRANSLATED CODE**\n\n";
    for (int i = 0; i < std::size(a); i++)
    {
        std::cout << a[i] << std::endl;
    }


}
