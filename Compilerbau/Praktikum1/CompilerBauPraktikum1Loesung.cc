
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

/* ZA */
std::vector<std::string> keys = {"MODULE", "ARRAY", "BEGIN", "CHAR", "CONST", "DO", "ELSE", "ELSIF", "END", "FOR", "IF", "INTEGER", "OF", "PROCEDURE", "REAL", "REPEAT", "RETURN", "THEN", "TO", "TYPE", "UNTIL", "VAR", "WHILE"};

/* error function */
void yyerror(const char *msg)
{
    std::cerr << "error: " << msg << std::endl;
    exit(1);
}

int main(int argc, char *argv[])
{
    /*	i/o handling */

    std::istream *yyin = &std::cin;
    std::ostream *yyout = &std::cout;
    std::ifstream inputFile;
    std::ofstream outputFile;

    if (argc > 3)
    {
        yyerror("wrong number of parameters");
    }
    if (argc > 1)
    {
        inputFile.open(argv[1]); /* redirect input */
        if (!inputFile)
        {
            yyerror("cannot open file for reading");
        }
        yyin = &inputFile;
    }
    if (argc > 2)
    {
        outputFile.open(argv[2]); /* redirect ouput */
        if (!outputFile)
        {
            yyerror("cannot open file for writing");
        }
        yyout = &outputFile;
    }

    /* get identifiers */

    std::string yytext;
    char c; /* current character */
    while (yyin->get(c))
    { /* while end of file is not reached */

        if (isalpha(c))
        { /* a new identifier starts */

            while (isalpha(c) || isdigit(c))
            { /* the identifier continues */
                yytext += c;
                yyin->get(c);
            }

            /* identifier ends (i.e. whitespace, semicolon oder point) */

            /* print and reset */
            /* ZA: print only if none of the keys */
            if (std::find(keys.begin(), keys.end(), yytext) == keys.end())
            {
                *yyout << yytext << std::endl;
            }
            yytext.clear();
        }
    }
    // inputFile und outputFile gehen out of scope und werden automatisch geclosed
    return 0;
}