#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using std::cout;
using std::cin;
using std::cerr;
using std::string;

void yyerror(string msg)
{
    cerr << "error: " << msg << '\n';
    std::exit(1);
}

void flush_ident(string& buf, std::ostream& out)
{
    if (!buf.empty())
    {
        out << buf << '\n';
        buf.clear();
    }
}

void scan(std::istream& in, std::ostream& out)
{
    enum State { NORMAL, IDENT, COMMENT};
    State st = State::NORMAL;

    string word_buff;
    int ch;
    while((ch = in.get()) != EOF)
    {
        unsigned char c = static_cast<unsigned char>(ch);
        switch (st)
        {
        case State::NORMAL:
            if(c == '(' && in.peek() == '*')
            {
                in.get();
                st = State::COMMENT;
                break;
            }
            if(std::isalpha(c))
            {
                word_buff.clear();
                word_buff.push_back(static_cast<char>(c));
                st = State::IDENT;
                break;
            }
            break;
        
        case State::IDENT:
            if(std::isalnum(c))
            {
                word_buff.push_back(static_cast<char>(c));
            } else {
                flush_ident(word_buff, out);
                st = State::NORMAL;
                if(c == '(' && in.peek() == '*')
                {
                    in.get();
                    st = State::COMMENT;
                }
            }
            break;
        
        case State::COMMENT:
            if(c == '*' && in.peek() == ')')
            {
                in.get();
                st = State::NORMAL;
            }    
            break;
        }
    }

    if(st == State::IDENT)
    {
        flush_ident(word_buff, out);
    }
}


int main(int argc, char** argv)
{
    std::istream* in = &std::cin;
    std::ostream* out = &std::cout;

    std::ifstream infile;
    std::ofstream outfile;


    if(argc >= 2)
    {
        infile.open(argv[1]);
        if(!infile.is_open())
        {
            yyerror("cannot open file for reading");
        }
        in = &infile;
    }

    if(argc == 3)
    {
        outfile.open(argv[2]);
        if(!outfile.is_open())
        {
            yyerror("cannot open file for writing");
        }
        out = &outfile;
    }

    scan(*in, *out);
    return 0;
}