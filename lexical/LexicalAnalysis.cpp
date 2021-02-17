#include <cstdio>
#include <cctype>
#include <cassert>

#include "LexicalAnalysis.h"

LexicalAnalysis::LexicalAnalysis(const char* filename) : m_line(1) {
    m_file = fopen(filename, "r");
    if (!m_file)
        throw "Unable to open file";
}

LexicalAnalysis::~LexicalAnalysis() {
    fclose(m_file);
}

int LexicalAnalysis::line() const {
    return m_line;
}

void myUngetc(int c, FILE *input, int *state, struct Lexeme *lex){
    if(c == EOF) {
        *state = 13;
        lex->type = TKN_UNEXPECTED_EOF;
    } else ungetc(c,input);
}

struct Lexeme LexicalAnalysis::nextToken() {
    struct Lexeme lex = { "", TKN_END_OF_FILE };

    int state = 1;
    while (state != 12 && state != 13) {
        int c = getc(m_file);
        
        switch (state) {
            case 1:
                switch (c) {
                    case '\n':
                        m_line++;
                    case '\t':
                    case '\r':
                    case ' ':
                        break;
                        
                    case EOF:
                        state = 13;
                        break;

                    case '(':
                        state = 2;
                        lex.token += (char) c;
                        break;

                    case '<':
                        state = 5;
                        lex.token += (char) c;
                        break;

                    case '>':
                        state = 6;
                        lex.token += (char) c;
                        break;

                    case ':':
                        state = 7;
                        lex.token += (char) c;
                        break;

                    case '\'':
                        state = 11;
                        lex.type = TKN_STRING;
                        break;

                    case '.':
                    case ',':
                    case ';':
                    case '=':
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '%':
                    case ')':
                        state = 12;
                        lex.token += (char) c;
                        break;

                    default:
                        lex.token += (char) c;
                        if(isdigit(c)) {
                            state = 9;
                            lex.type = TKN_INTEGER;
                        } else if(c == '_' || isalpha(c)) state = 8;
                        else {
                            state = 13;
                            lex.type = TKN_INVALID_TOKEN;
                        }
                        break;
                }
                break;

            case 2:
                if(c == '*') {
                    lex.token = "";
                    state = 3;
                } else {
                    state = 12;
                    myUngetc(c,m_file, &state, &lex);
                }
                break;

            case 3:
                if(c == '*') state = 4;
                if(c == '\n') m_line++;
                break;

            case 4:
                if(c == '\n') m_line++;
                if(c == ')') state = 1;
                else if(c != '*') state = 3;
                break;

            case 5:
                state = 12;
                if(c != '=' && c != '>') myUngetc(c,m_file, &state, &lex);
                else lex.token += (char) c;
                break;

            // Os dois estados vão ter o mesmo comportamento
            case 6:
            case 7:
                state = 12;
                if(c != '=') myUngetc(c,m_file, &state, &lex);
                else lex.token += (char) c;
                break;

            case 8:
                if(c == '_' || isalpha(c)) lex.token += (char) c;
                else {
                    state = 12;
                    myUngetc(c,m_file, &state, &lex);
                }
                break;

            case 9:
                if(isdigit(c)) lex.token += (char) c;
                else if(c == '.'){
                    state = 10;
                    lex.token += (char) c;
                    lex.type = TKN_REAL;
                } else {
                    state = 13;
                    myUngetc(c,m_file, &state, &lex);
                }
                break;

            case 10:
                if(isdigit(c))
                    lex.token += (char) c;
                else {
                    state = 13;
                    myUngetc(c,m_file, &state, &lex);
                }
                break;

            case 11:
                if(c == EOF){
                    lex.type = TKN_UNEXPECTED_EOF;
                    state = 13;
                }else{
                    if(c == '\'') {
                        state = 13;
                        break;
                    }
                    if(c == '\n') m_line++;
                    lex.token += (char) c;
                }
                break;

            default:
                assert(false);
        }
    }

    if (state == 12) lex.type = m_st.find(lex.token);

    return lex;
}
