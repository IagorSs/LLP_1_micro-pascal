#include <cstdlib>
#include "SyntaticAnalysis.h"

#include "../interpreter/command/Command.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
    m_lex(lex), m_current(m_lex.nextToken()) {
}

SyntaticAnalysis::~SyntaticAnalysis() {
}

Command* SyntaticAnalysis::start() {
    return 0;
}

void SyntaticAnalysis::advance() {
    // printf("Advanced (\"%s\", %d)\n",
    //     m_current.token.c_str(), m_current.type);
    m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
    // printf("Expected (..., %d), found (\"%s\", %d)\n",
    //     type, m_current.token.c_str(), m_current.type);
    if (type == m_current.type) {
        m_current = m_lex.nextToken();
    } else {
        showError();
    }
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
}

// <const>    ::= <id> = <value> ';'
void SyntaticAnalysis::procConst() {
}

// <var>      ::= <id> { ',' <id> } [ = <value> ] ';'
void SyntaticAnalysis::procVar() {
}

// <body>     ::= <block> | <cmd>
void SyntaticAnalysis::procBody() {
    if (m_current.type == TKN_BLOCK){
        procBlock();
    }
    else{
        procCmd();
    } 
}

// <block>    ::= begin [ <cmd> { ';' <cmd> } ] end
void SyntaticAnalysis::procBlock() {
}

// <cmd>      ::= <assign> | <if> | <case> | <while> | <for> | <repeat> | <write> | <read>
void SyntaticAnalysis::procCmd() {
    if(m_current.type == TKN_ID){
        procAssign();
    }
    else if(m_current.type == TKN_IF){
        procIf();
    }
    else if(m_current.type == TKN_CASE){
        procCase();
    }
    else if(m_current.type == TKN_WHILE){
        procWhile();
    }
    else if(m_current.type == TKN_FOR){
        procFor();
    }
    else if(m_current.type == TKN_REPEAT){
        procRepeat();
    }
    else if(m_current.type == TKN_WRITE){
        procWrite();
    }
    else if(m_current.type == TKN_READLN){
        procRead();
    }
    else{
        showError();
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
    if (m_current.type == TKN_ELSE)
    {
        advance();
        procBody();
    }
}

// <case>     ::= case <expr> of { <value> : <body> ';' } [ else <body> ';' ] end
void SyntaticAnalysis::procCase() {
}

// <while>    ::= while <boolexpr> do <body>
void SyntaticAnalysis::procWhile() {
    eat(TKN_WHILE);
    procBoolExpr();
    eat(TKN_DO);
    procBody();
   // eat(Tkn_d)
}

// <repeat>   ::= repeat [ <cmd> { ';' <cmd> } ] until <boolexpr>
void SyntaticAnalysis::procRepeat() {
}

// <for>      ::= for <id> := <expr> to <expr> do <body>
void SyntaticAnalysis::procFor() {
    eat(TKN_FOR);
    eat(TKN_ASSIGN);
    procExpr();
    eat(TKN_TO);
    procExpr();
    eat(TKN_DO);
    procBody();
}

// <write>    ::= (write | writeln) '(' [ <expr> { ',' <expr> } ] ')'
void SyntaticAnalysis::procWrite() {
}

// <read>     ::= readln '(' <id> { ',' <id> } ')'
void SyntaticAnalysis::procRead() {
}

// <boolexpr> ::= [ not ] <cmpexpr> [ (and | or) <boolexpr> ]
void SyntaticAnalysis::procBoolExpr() {
}

// <cmpexpr>  ::= <expr> ('=' | '<>' | '<' | '>' | '<=' | '>=') <expr>
void SyntaticAnalysis::procCmpExpr() {
}

// <expr>     ::= <term> { ('+' | '-') <term> }
void SyntaticAnalysis::procExpr() {
}

// <term>     ::= <factor> { ('*' | '/' | '%') <factor> }
void SyntaticAnalysis::procTerm() {
}

// <factor>   ::= <value> | <id> | '(' <expr> ')'
void SyntaticAnalysis::procFactor() {
}

// <value>    ::= <integer> | <real> | <string>
void SyntaticAnalysis::procValue() {
}

void SyntaticAnalysis::procId() {
}

void SyntaticAnalysis::procInteger() {
}

void SyntaticAnalysis::procReal() {
}

void SyntaticAnalysis::procString() {
    
}
