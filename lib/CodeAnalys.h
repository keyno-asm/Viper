#include<vector>
#include<string>

#define STRVEC std::vector<std::string>
#define STR std::string
#define STRVV std::vector<std::vector<std::string>>

/*
void SyntaxAnalys(STRVEC code)
{

}*/

STR lexems[] = {
    "print",
    "input",
    "int",
    "double",
    "mem"
};

STRVEC VecConcat(STRVEC a, STRVEC b)
{
    STRVEC ret = a;
    for (STR line : b)
    {
        ret.push_back(line);
    }

    return ret;
}

STRVEC KillerOfFuckingNullStrings(STRVEC vec)
{
    STRVEC ret;
    for (STR line : vec)
    {
        if (line[0] != '\0' && line[0] != '\n')
        {
            ret.push_back(line);
        }
    }

    return ret;
}

STRVEC Tokenize(STRVEC code)
{
    STRVEC ret;
    bool SSF = false;

    //This is very awful hack, I'll do better later if I don't forget...
    for (STR line : code)
    {
        STRVEC sep_string;
        STR str = "";
        for (char c : line)
        {
            switch (c)
            {
            case ' ':
                sep_string.push_back(str);
                str = "";
                break;
            case '(':
                sep_string.push_back(str);
                sep_string.push_back("ARGS");
                str = "";
                break;
            case ')':
                sep_string.push_back(str);
                sep_string.push_back("ARGe");
                str = "";
                break;
            case ',':
                sep_string.push_back(str);
                sep_string.push_back("AND");
                str = "";
                break;
            case '\"':
                sep_string.push_back(str);
                if (!SSF) 
                {
                    sep_string.push_back("STR");
                    SSF += 1;
                }
                else if (SSF)
                { 
                    SSF -= 1; 
                    sep_string.push_back("STRe");
                }
                str = "";
                break;
            
            default:
                str += c;
                break;
            }

        }

        ret = VecConcat(ret, sep_string);
        sep_string.clear();

    }

    return KillerOfFuckingNullStrings(ret);
}