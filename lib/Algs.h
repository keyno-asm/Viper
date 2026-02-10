#include<vector>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>

#define STRVEC std::vector<std::string>
#define STR std::string

STRVEC Reader(STR path)
{
    STR line;
    STRVEC ret;
    std::ifstream file(path);
    if(file.is_open())
    {
        while(std::getline(file, line))
        {
            ret.push_back(line);
        }
    }
    else {
        printf("No such file in this directory");
    }
    file.close();

    return ret;
}

STRVEC Writer(STRVEC text, STR path)
{
    std::ofstream file(path);

    if(file.is_open())
    {
        for (STR str : text)
        {
            file << str ;
        }
    }
}

