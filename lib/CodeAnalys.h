#include<vector>
#include<string>
#include<stdio.h>

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

//This function is not tested, and I do not know how well it works. And I know, it's awful
STR OneInstTranslate(STRVEC tokens)
{
    STR ret = "";
    for (int i = 0; i < std::size(tokens); i++) {
        //Default functions
        if (tokens[i] == "print") {
            ret += "std::cout ";
            for (int j = i + 1; j < std::size(tokens); j++) {
                if (tokens[j] == "STR") {
                    ret += "\"";

                }
                else if (tokens[j] == "STRe") {
                    ret += "\"";

                }
                else if (tokens[j] == "AND" || tokens[j] == "ARGS") {
                    ret += "<<";

                }
                else if (tokens[j] == "ARGe")
                {
                    ret += ";\n";
                    i += j - i;
                    break;

                }
                else if (tokens[j] == "EQU")
                {
                    continue;
                }
                else {
                    ret += tokens[j] + ' ';
                }
            }
        }
        else if (tokens[i] == "input") {
            ret += "std::cin ";
            for (int j = i + 1; j < std::size(tokens) ; j++)
            {
                if (tokens[j] == "AND")
                {
                    ret += ">> ";

                }
                else if (tokens[j] == "ARGS")
                {
                    ret += ">> ";

                }
                else if (tokens[j] == "ARGe")
                {
                    ret += ";\n";
                    i += j - i;
                    break;

                }
                else {
                    ret += tokens[j];

                }
            }
        }
        //Data types
        else if (tokens[i] == "int") {
            ret += "int ";
            for (int j = i + 2; j < std::size(tokens); j++)
            {
                if (tokens[j] == "EQU")
                {
                    ret += "= ";
                    ret += tokens[j + 1];
                    if (tokens[j + 2] != "AND")
                    {
                        ret += ";\n";
                        i += (j + 2) - i;
                    }
                }
                else if (tokens[j] == "STR" || tokens[j] == "STRe" || tokens[j] == "ARGS" || tokens[j] == "ARGe")
                {
                    continue;
                }
                else ret += tokens[j] + ' ';
            }
        }
        else if (tokens[i] == "double") {
            ret += "double";
        }
        else {
            printf("Unknown function!");
        }
    }
        ret += "\n";
        return ret;
}

STRVV Tokens(STRVEC code)
{
    STRVV ret;
    bool SSF = false;

    for (STR line : code)
    {   
        STRVEC tmp;
        STR str;
        for (char c : line)
        {
            switch (c)
            {
                case ' ':
                    tmp.push_back(str);
                    str = "";
                    break;
                case '(':
                    tmp.push_back(str);
                    tmp.push_back("ARGS");
                    str = "";
                    break;
                case ')':
                    tmp.push_back(str);
                    tmp.push_back("ARGe");
                    str = "";
                    break;
                case '\"':
                    tmp.push_back(str);
                    if (!SSF)
                    {
                        tmp.push_back("STR");
                        SSF += 1;
                    }
                    else {
                        tmp.push_back("STRe");
                        SSF -= 1;
                    }
                    str = "";
                    break;
                case ',':
                    tmp.push_back(str);
                    tmp.push_back("AND");
                    str = "";
                    break;

                case '=':
                    tmp.push_back(str);
                    tmp.push_back("EQU");
                    str = "";
                    break;
                case '+':
                    tmp.push_back(str);
                    tmp.push_back("PLUS");
                    str = "";
                    break;
                case '\\':
                    tmp.push_back(str);
                    str = "";
                    break;
                case '{':
                    tmp.push_back(str);
                    tmp.push_back("FOP");
                    str = "";
                    break;
                case '}':
                    tmp.push_back(str);
                    tmp.push_back("FCL");
                    str = "";
                    break;
                case ':':
                    tmp.push_back(str);
                    tmp.push_back("DPC");
                    str = "";
                    break;
                default:
                    str += c;
                    break;
            }
        }
        tmp.push_back(str);
        str = "";
        ret.push_back(tmp);
    }
    return ret;
}

STRVEC TranslateCpp(STRVV tokens)
{
    STRVEC ret;

    for (STRVEC tline : tokens)
    {   
        STR tmp;
        for (int i  = 0; i < std::size(tline) ; i++)
        {
            //data types check
            if (tline[i] == "int")
            {
                tmp += "int ";
                for (int j = i + 1; j < std::size(tline); j++)
                {
                    if (tline[j] == "EQU")
                    {
                        tmp += " = ";
                    }
                    else if (tline[j] == "PLUS")
                    {
                        tmp += " + ";
                    }
                    else{
                        tmp += tline[j];
                    }

                }
                tmp += ";";  
            }

            else if (tline[i] == "double")
            {
                tmp += "double ";
                for (int j = i + 1; j < std::size(tline); j++)
                {
                    if (tline[j] == "EQU")
                    {
                        tmp += " = ";
                    }
                    else if (tline[j] == "PLUS")
                    {
                        tmp += " + ";
                    }
                    else{
                        tmp += tline[j];
                    }

                }
                tmp += ";";
            }
            //stdio functions check
            else if (tline[i] == "print")
            {
                tmp = "std::cout << ";
                for (int j = i + 1 ; j < std::size(tline); j++)
                {
                    if (tline[j] == "STR" || tline[j] ==  "STRe")
                    {
                        tmp += "\"";
                    }
                    else if (tline[j] == "AND" || tline [j] == "PLUS"){
                        tmp += " << ";
                    }
                    else if (tline[j] == "ARGS" || tline[j] == "ARGe")
                    {
                        continue;
                    }
                    else {
                        tmp += tline[j] + ' ';
                    }
                }
                tmp += ";";
            }
            else if (tline[i] == "input")
            {
                tmp += "std::cin >> ";
                for (int j = i + 1; j < std::size(tline); j++)
                {
                    if (tline[j] == "ARGS" || tline[j] == "ARGe")
                    {
                        continue;
                    }
                    else if (tline[j] == "AND" || tline[j] == "PLUS")
                    {
                        tmp += ">>";
                    }
                    else{
                        tmp += tline[j] + ' ';
                    }
                }
                tmp += ";";
            }
            /*
            else if (tline[i] == "if")
            {
                tmp += "if";
                for (int j = i + 1; j < std::size(tline); j++)
                {
                    if (tline[j] == "ARGS")
                    {
                        tmp += "(";

                    }
                }
            }*/
        }
        ret.push_back(tmp);
        tmp = "";
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
            case '\\'://Comments
                sep_string.push_back(str);
                str = "";
                break;
            case '=':
                sep_string.push_back(str);
                sep_string.push_back("EQU");
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
