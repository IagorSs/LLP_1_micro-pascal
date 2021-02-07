#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    // SYMBOLS
    m_st["."] = TKN_DOT;
    m_st[","] = TKN_COMMA;
    m_st[":"] = TKN_COLON;
    m_st[";"] = TKN_SEMICOLON;
    m_st["("] = TKN_OPEN_PAR;
    m_st[")"] = TKN_CLOSE_PAR;

    // OPERATORS
    m_st[":="] = TKN_ASSIGN;
    m_st["="] = TKN_EQUAL;
    m_st["<>"] = TKN_NOT_EQUAL;
    m_st["<"] = TKN_LOWER;
    m_st[">"] = TKN_GREATER;
    m_st["<="] = TKN_LOWER_EQ;
    m_st[">="] = TKN_GREATER_EQ;
    m_st["+"] = TKN_ADD;
    m_st["-"] = TKN_SUB;
    m_st["*"] = TKN_MUL;
    m_st["/"] = TKN_DIV;
    m_st["%"] = TKN_MOD;

    // KEYWORDS
    m_st["program"] = TKN_PROGRAM;
    m_st["const"] = TKN_CONST;
    m_st["var"] = TKN_VAR;
    m_st["begin"] = TKN_BEGIN;
    m_st["end"] = TKN_END;
    m_st["if"] = TKN_IF;
    m_st["then"] = TKN_THEN;
    m_st["else"] = TKN_ELSE;
    m_st["case"] = TKN_CASE;
    m_st["of"] = TKN_OF;
    m_st["while"] = TKN_WHILE;
    m_st["do"] = TKN_DO;
    m_st["repeat"] = TKN_REPEAT;
    m_st["until"] = TKN_UNTIL;
    m_st["for"] = TKN_FOR;
    m_st["to"] = TKN_TO;
    m_st["write"] = TKN_WRITE;
    m_st["writeln"] = TKN_WRITELN;
    m_st["readln"] = TKN_READLN;
    m_st["not"] = TKN_NOT;
    m_st["and"] = TKN_AND;
    m_st["or"] = TKN_OR;
}

SymbolTable::~SymbolTable() {
}

bool SymbolTable::contains(std::string token) {
    return m_st.find(token) != m_st.end();
}

enum TokenType SymbolTable::find(std::string token) {
    return this->contains(token) ? m_st[token] : TKN_ID;
}
