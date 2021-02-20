#include <cstdlib>
#include <iostream>
#include "SyntaticAnalysis.h"

#include "../interpreter/command/Command.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis &lex) : m_lex(lex), m_current(m_lex.nextToken()) {
}

SyntaticAnalysis::~SyntaticAnalysis() {
}

Command *SyntaticAnalysis::start() {
    procProgram();
    eat(TKN_END_OF_FILE);
}

void SyntaticAnalysis::advance() {
    m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
    if( type == TKN_END_OF_FILE){
        std::cout << "CHEGOU AO FIM " << type << std::endl;
    }
    if (type == m_current.type) m_current = m_current.type != TKN_END_OF_FILE ? m_lex.nextToken():m_current;
    else showError();
}

void SyntaticAnalysis::showError() {
    printf("%02d: ", m_lex.line());

    switch (m_current.type) {
        case TKN_INVALID_TOKEN:
            printf("Lexema inválido [%s]\n", m_current.token.c_str());
            break;
        case TKN_UNEXPECTED_EOF:
        case TKN_END_OF_FILE:
            printf("Fim de arquivo inesperado\n");
            break;
        default:
            printf("Lexema não esperado [%s]\n", m_current.token.c_str());
            break;
    }

    exit(1);
}

// <program>  ::= program <id> ';'
//                [ const <const> { <const> } ]
//                [ var <var> { <var> } ]
//                <block> '.'
void SyntaticAnalysis::procProgram() {
    eat(TKN_PROGRAM);
    procId();
    eat(TKN_SEMICOLON);
    if(m_current.type == TKN_CONST){
        advance();
        procConst();
        
        while (m_current.type == TKN_ID) procConst();
    }
    if(m_current.type == TKN_VAR){
        advance();
        procVar();
        while (m_current.type == TKN_ID) procVar();
    }
    procBlock();
    eat(TKN_DOT);
}

// <const>    ::= <id> = <value> ';'
void SyntaticAnalysis::procConst() {
    procId();
    eat(TKN_EQUAL);
    procValue();
    eat(TKN_SEMICOLON);
}

// <var>      ::= <id> { ',' <id> } [ = <value> ] ';'
void SyntaticAnalysis::procVar() {
    procId();
    while (m_current.type == TKN_COMMA){
        advance();
        procId();
    }
    if(m_current.type == TKN_EQUAL){
        advance();
        procValue();
    }
    eat(TKN_SEMICOLON);
}

// <body>     ::= <block> | <cmd>
void SyntaticAnalysis::procBody() {
    if (m_current.type == TKN_BEGIN) procBlock();
    else procCmd();
}

// <block>    ::= begin [ <cmd> { ';' <cmd> } ] end
void SyntaticAnalysis::procBlock() {
    eat(TKN_BEGIN);

    if ((m_current.type == TKN_ID) || (m_current.type == TKN_IF)
        || (m_current.type == TKN_CASE)|| (m_current.type == TKN_WHILE)
        || (m_current.type == TKN_FOR) || (m_current.type == TKN_REPEAT)
        || (m_current.type == TKN_WRITE) || (m_current.type == TKN_READLN)
        || (m_current.type == TKN_WRITELN)){
        procCmd();

        while (m_current.type == TKN_SEMICOLON){
            advance();
            procCmd();
        }
    }

    eat(TKN_END);
}

// <cmd>      ::= <assign> | <if> | <case> | <while> | <for> | <repeat> | <write> | <read>
void SyntaticAnalysis::procCmd() {
    switch (m_current.type) {
        case TKN_ID:
            procAssign();
            break;

        case TKN_IF:
            procIf();
            break;

        case TKN_CASE:
            procCase();
            break;

        case TKN_WHILE:
            procWhile();
            break;

        case TKN_FOR:
            procFor();
            break;

        case TKN_REPEAT:
            procRepeat();
            break;

        case TKN_WRITELN:
        case TKN_WRITE:
            procWrite();
            break;

        case TKN_READLN:
            procRead();
            break;

        default: showError();
    }
}

// <assign>   ::= <id> := <expr>
void SyntaticAnalysis::procAssign() {
    procId();
    eat(TKN_ASSIGN);
    procExpr();
}

// <if>       ::= if <boolexpr> then <body> [else <body>]
void SyntaticAnalysis::procIf() {
    eat(TKN_IF);
    procBoolExpr();
    eat(TKN_THEN);
    procBody();

    if (m_current.type == TKN_ELSE){
        advance();
        procBody();
    }
}

// <case>     ::= case <expr> of { <value> : <body> ';' } [ else <body> ';' ] end
void SyntaticAnalysis::procCase() {
    eat(TKN_CASE);
    procExpr();
    eat(TKN_OF);

    while ((m_current.type == TKN_INTEGER) || (m_current.type == TKN_REAL)
        || (m_current.type == TKN_STRING)) {
        procValue();
        eat(TKN_COLON);
        procBody();
        eat(TKN_SEMICOLON);
    }

    if (m_current.type == TKN_ELSE) {
        advance();
        procBody();
        eat(TKN_SEMICOLON);
    }

    eat(TKN_END);
}

// <while>    ::= while <boolexpr> do <body>
void SyntaticAnalysis::procWhile() {
    eat(TKN_WHILE);
    procBoolExpr();
    eat(TKN_DO);
    procBody();
}

// <repeat>   ::= repeat [ <cmd> { ';' <cmd> } ] until <boolexpr>
void SyntaticAnalysis::procRepeat() {
    eat(TKN_REPEAT);
    
    if((m_current.type == TKN_ID) || (m_current.type == TKN_IF)
        || (m_current.type == TKN_CASE)|| (m_current.type == TKN_WHILE)
        || (m_current.type == TKN_FOR) || (m_current.type == TKN_REPEAT)
        || (m_current.type == TKN_WRITE) || (m_current.type == TKN_READLN)
        || (m_current.type == TKN_WRITELN)){
        procCmd();

        while (m_current.type == TKN_SEMICOLON) {
            advance();
            procCmd();
        }
    }
    eat(TKN_UNTIL);
    procBoolExpr();
}

// <for>      ::= for <id> := <expr> to <expr> do <body>
void SyntaticAnalysis::procFor() {
    eat(TKN_FOR);
    procId();
    eat(TKN_ASSIGN);
    procExpr();
    eat(TKN_TO);
    procExpr();
    eat(TKN_DO);
    procBody();
}

// <write>    ::= (write | writeln) '(' [ <expr> { ',' <expr> } ] ')'
void SyntaticAnalysis::procWrite() {
    if (m_current.type == TKN_WRITE) eat(TKN_WRITE);
    else if (m_current.type == TKN_WRITELN) eat(TKN_WRITELN);

    eat(TKN_OPEN_PAR);

    if(m_current.type == TKN_INTEGER || m_current.type == TKN_REAL
        || m_current.type == TKN_STRING || m_current.type == TKN_ID
        || m_current.type == TKN_OPEN_PAR){
        procExpr();

        while (m_current.type == TKN_COMMA) {
            advance();
            procExpr();
        }
    }

    eat(TKN_CLOSE_PAR);

}

// <read>     ::= readln '(' <id> { ',' <id> } ')'
void SyntaticAnalysis::procRead() {
    eat(TKN_READLN);
    eat(TKN_OPEN_PAR);
    procId();

    while (m_current.type == TKN_COMMA){
        advance();
        procId();
    }
    
    eat(TKN_CLOSE_PAR);
}

// <boolexpr> ::= [ not ] <cmpexpr> [ (and | or) <boolexpr> ]
void SyntaticAnalysis::procBoolExpr() {
    if (m_current.type == TKN_NOT) advance();

    procCmpExpr();

    if (m_current.type == TKN_AND || m_current.type == TKN_OR){
        advance();
        procBoolExpr();
    }
}

// <cmpexpr>  ::= <expr> ('=' | '<>' | '<' | '>' | '<=' | '>=') <expr> |
//            '(' <expr> ('=' | '<>' | '<' | '>' | '<=' | '>=') <expr> ')'
void SyntaticAnalysis::procCmpExpr() {
    bool existPar = m_current.type == TKN_OPEN_PAR;

    if (existPar) eat(TKN_OPEN_PAR);

    procExpr();

    switch (m_current.type){
        case TKN_EQUAL:
        case TKN_NOT_EQUAL:
        case TKN_LOWER:
        case TKN_GREATER:
        case TKN_LOWER_EQ:
        case TKN_GREATER_EQ:
            advance();
            break;

        default: showError();
    }

    procExpr();

    if (existPar) eat(TKN_CLOSE_PAR);
}

// <expr>     ::= <term> { ('+' | '-') <term> }
void SyntaticAnalysis::procExpr() {
    procTerm();

    while ((m_current.type == TKN_ADD) || (m_current.type == TKN_SUB)) {
        advance();
        procTerm();
    }
}

// <term>     ::= <factor> { ('*' | '/' | '%') <factor> }
void SyntaticAnalysis::procTerm() {
    procFactor();

    while ((m_current.type == TKN_MUL) || (m_current.type == TKN_DIV) || (m_current.type == TKN_MOD)) {
        advance();
        procFactor();
    }
    
}

// <factor>   ::= <value> | <id> | '(' <expr> ')'
void SyntaticAnalysis::procFactor() {
    switch(m_current.type){
        case TKN_INTEGER:
        case TKN_REAL:
        case TKN_STRING:
            procValue();
            break;

        case TKN_ID:
            procId();
            break;

        default:
            eat(TKN_OPEN_PAR);
            procExpr();
            eat(TKN_CLOSE_PAR);
    }
}

// <value>    ::= <integer> | <real> | <string>
void SyntaticAnalysis::procValue() {
    switch(m_current.type){
        case TKN_INTEGER:
            procInteger();
            break;

        case TKN_REAL:
            procReal();
            break;
        
        case TKN_STRING:
            procString();
            break;
        
        default: showError();
    }
}

void SyntaticAnalysis::procId() {
    eat(TKN_ID);
}

void SyntaticAnalysis::procInteger() {
    eat(TKN_INTEGER);
}

void SyntaticAnalysis::procReal() {
    eat(TKN_REAL);
}

void SyntaticAnalysis::procString() {
    eat(TKN_STRING);
}
