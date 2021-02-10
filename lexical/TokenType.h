#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType {
    // SPECIALS
    TKN_UNEXPECTED_EOF = -2,
    TKN_INVALID_TOKEN = -1,
    TKN_END_OF_FILE = 0,

    // SYMBOLS
    TKN_DOT,           // .
    TKN_COMMA,         // ,
    TKN_COLON,         // :
    TKN_SEMICOLON,     // ;
    TKN_OPEN_PAR,      // (
    TKN_CLOSE_PAR,     // )

    // OPERATORS
    TKN_ASSIGN,        // :=
    TKN_EQUAL,         // =
    TKN_NOT_EQUAL,     // <>
    TKN_LOWER,         // <
    TKN_GREATER,       // >
    TKN_LOWER_EQ,      // <=
    TKN_GREATER_EQ,    // >=
    TKN_ADD,           // +
    TKN_SUB,           // -
    TKN_MUL,           // *
    TKN_DIV,           // /
    TKN_MOD,           // %

    // KEYWORDS
    TKN_PROGRAM,       // program
    TKN_CONST,         // const
    TKN_VAR,           // var
    TKN_BEGIN,         // begin
    TKN_END,           // end
    TKN_IF,            // if
    TKN_THEN,          // then
    TKN_ELSE,          // else
    TKN_CASE,          // case
    TKN_OF,            // of
    TKN_WHILE,         // while
    TKN_DO,            // do
    TKN_REPEAT,        // repeat
    TKN_UNTIL,         // until
    TKN_FOR,           // for
    TKN_TO,            // to
    TKN_WRITE,         // write
    TKN_WRITELN,       // writeln
    TKN_READLN,        // readln
    TKN_NOT,           // not
    TKN_AND,           // and
    TKN_OR,            // or

    // OTHERS
    TKN_ID,            // identifier
    TKN_INTEGER,       // integer
    TKN_REAL,          // real
    TKN_STRING,        // string

};

#endif
