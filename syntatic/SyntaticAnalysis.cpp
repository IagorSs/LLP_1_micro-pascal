#include <cstdlib>
#include <iostream>
#include "SyntaticAnalysis.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis &lex) : m_lex(lex), m_current(m_lex.nextToken()) {
}

SyntaticAnalysis::~SyntaticAnalysis() {
}

Command* SyntaticAnalysis::start() {
    Command* c = procProgram();
    eat(TKN_END_OF_FILE);
    return c;
}

void SyntaticAnalysis::advance() {
    m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
    if (type == m_current.type) m_current = m_current.type == TKN_END_OF_FILE ? m_current:m_lex.nextToken();        
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
Command* SyntaticAnalysis::procProgram() {
    BlocksCommand* c = new BlocksCommand(m_lex.line());

    eat(TKN_PROGRAM);
    // Variável não está sendo usada para nada
    procId();
    eat(TKN_SEMICOLON);
    if(m_current.type == TKN_CONST){
        advance();
        c->addCommand(procConst());
        
        while (m_current.type == TKN_ID) c->addCommand(procConst());
    }
    if(m_current.type == TKN_VAR){
        advance();
        c->addCommand(procVar());
        while (m_current.type == TKN_ID) c->addCommand(procVar());
    }

    c->addCommand(procBlock());
    eat(TKN_DOT);
    return c;
}

// <const>    ::= <id> = <value> ';'
AssignCommand* SyntaticAnalysis::procConst() {
    Variable* var = procId();
    var->setConst();
    eat(TKN_EQUAL);
    Type* value= procValue();
    eat(TKN_SEMICOLON);

    ConstExpr* expr = new ConstExpr(m_lex.line(), value);

    return new AssignCommand(m_lex.line(), var, expr);
}

// <var>      ::= <id> { ',' <id> } [ = <value> ] ';'
AssignCommand* SyntaticAnalysis::procVar() {
    Variable* var;

    var = procId();
    ConstExpr* expr = new ConstExpr(m_lex.line(), new IntegerValue(0));

    while (m_current.type == TKN_COMMA){
        advance();
        var = procId();
    }
    if(m_current.type == TKN_EQUAL){
        advance();
        expr = new ConstExpr(m_lex.line() ,procValue());
    }
    eat(TKN_SEMICOLON);

    AssignCommand* ac = new AssignCommand(m_lex.line(), var, expr);

    return ac;
}

// <body>     ::= <block> | <cmd>
Command* SyntaticAnalysis::procBody() {
    if (m_current.type == TKN_BEGIN) return procBlock();
    return procCmd();
}

// <block>    ::= begin [ <cmd> { ';' <cmd> } ] end
BlocksCommand* SyntaticAnalysis::procBlock() {
    eat(TKN_BEGIN);

    BlocksCommand* c = new BlocksCommand(m_lex.line());

    if ((m_current.type == TKN_ID) || (m_current.type == TKN_IF)
        || (m_current.type == TKN_CASE)|| (m_current.type == TKN_WHILE)
        || (m_current.type == TKN_FOR) || (m_current.type == TKN_REPEAT)
        || (m_current.type == TKN_WRITE) || (m_current.type == TKN_READLN)
        || (m_current.type == TKN_WRITELN)){
        c->addCommand(procCmd());

        while (m_current.type == TKN_SEMICOLON){
            advance();
            c->addCommand(procCmd());
        }
    }

    eat(TKN_END);
    return c;
}

// <cmd>      ::= <assign> | <if> | <case> | <while> | <for> | <repeat> | <write> | <read>
Command* SyntaticAnalysis::procCmd() {
    switch (m_current.type) {
        case TKN_ID: return procAssign();

        case TKN_IF: return procIf();

        case TKN_CASE: return procCase();

        case TKN_WHILE: return procWhile();

        case TKN_FOR: return procFor();

        case TKN_REPEAT: return procRepeat();

        case TKN_WRITELN:
        case TKN_WRITE: return procWrite();

        case TKN_READLN: return procRead();

        default: showError();
    }
}

// <assign>   ::= <id> := <expr>
AssignCommand* SyntaticAnalysis::procAssign() {
    Variable* var = procId();
    eat(TKN_ASSIGN);
    Expr* expr = procExpr();

    return new AssignCommand(m_lex.line(), var, expr);
}

// <if>       ::= if <boolexpr> then <body> [else <body>]
IfCommand* SyntaticAnalysis::procIf() {
    eat(TKN_IF);
    BoolExpr* expr = procBoolExpr();
    eat(TKN_THEN);

    Command* ifBody = procBody();

    IfCommand* c = new IfCommand(m_lex.line(), expr, ifBody);

    if (m_current.type == TKN_ELSE){
        advance();
        c->setElseCommands(procBody());
    }

    return c;
}

// <case>     ::= case <expr> of { <value> : <body> ';' } [ else <body> ';' ] end
CaseCommand* SyntaticAnalysis::procCase() {
    eat(TKN_CASE);
    Expr* expr_1 = procExpr();
    eat(TKN_OF);

    CaseCommand* c = new CaseCommand(m_lex.line(), expr_1);

    while ((m_current.type == TKN_INTEGER) || (m_current.type == TKN_REAL)
        || (m_current.type == TKN_STRING)) {
        Type* key = procValue();
        eat(TKN_COLON);
        Command* currentCmd = procBody();
        eat(TKN_SEMICOLON);

        c->addOption(key, currentCmd);
    }

    if (m_current.type == TKN_ELSE) {
        advance();
        c->setOtherwise(procBody());
        eat(TKN_SEMICOLON);
    }

    eat(TKN_END);

    return c;
}

// <while>    ::= while <boolexpr> do <body>
WhileCommand* SyntaticAnalysis::procWhile() {
    eat(TKN_WHILE);
    BoolExpr* expr = procBoolExpr();
    eat(TKN_DO);
    Command* cmds = procBody();

    return new WhileCommand(m_lex.line(), expr, cmds);
}

// <repeat>   ::= repeat [ <cmd> { ';' <cmd> } ] until <boolexpr>
RepeatCommand* SyntaticAnalysis::procRepeat() {
    BlocksCommand* cmds = new BlocksCommand(m_lex.line());
    eat(TKN_REPEAT);
    
    if((m_current.type == TKN_ID) || (m_current.type == TKN_IF)
        || (m_current.type == TKN_CASE)|| (m_current.type == TKN_WHILE)
        || (m_current.type == TKN_FOR) || (m_current.type == TKN_REPEAT)
        || (m_current.type == TKN_WRITE) || (m_current.type == TKN_READLN)
        || (m_current.type == TKN_WRITELN)){
        cmds->addCommand(procCmd());

        while (m_current.type == TKN_SEMICOLON) {
            advance();
            cmds->addCommand(procCmd());
        }
    }
    eat(TKN_UNTIL);
    BoolExpr* expr = procBoolExpr();

    return new RepeatCommand(m_lex.line(), cmds, expr);
}

// <for>      ::= for <id> := <expr> to <expr> do <body>
ForCommand* SyntaticAnalysis::procFor() {
    eat(TKN_FOR);
    Variable* var = procId();
    eat(TKN_ASSIGN);
    Expr* expr_1 = procExpr();
    eat(TKN_TO);
    Expr* expr_2 = procExpr();
    eat(TKN_DO);
    Command* cmds = procBody();

    return new ForCommand(m_lex.line(), var, expr_1, expr_2, cmds);
}

// <write>    ::= (write | writeln) '(' [ <expr> { ',' <expr> } ] ')'
WriteCommand* SyntaticAnalysis::procWrite() {
    bool isLn = false;

    if (m_current.type == TKN_WRITE) eat(TKN_WRITE);
    else if (m_current.type == TKN_WRITELN) {
        isLn = true;
        eat(TKN_WRITELN);
    }

    WriteCommand* c = new WriteCommand(m_lex.line(), isLn);

    eat(TKN_OPEN_PAR);

    if(m_current.type == TKN_INTEGER || m_current.type == TKN_REAL
        || m_current.type == TKN_STRING || m_current.type == TKN_ID
        || m_current.type == TKN_OPEN_PAR){
        c->addExpr(procExpr());

        while (m_current.type == TKN_COMMA) {
            advance();
            c->addExpr(procExpr());
        }
    }

    eat(TKN_CLOSE_PAR);

    return c;
}

// <read>     ::= readln '(' <id> { ',' <id> } ')'
ReadCommand* SyntaticAnalysis::procRead() {
    eat(TKN_READLN);
    eat(TKN_OPEN_PAR);
    ReadCommand* c = new ReadCommand(m_lex.line());

    Variable* var = procId();

    c->addVariable(var);

    while (m_current.type == TKN_COMMA){
        advance();
        Variable* var2 = procId();

        c->addVariable(var2);
    }
    
    eat(TKN_CLOSE_PAR);
    return c;
}

// <boolexpr> ::= [ not ] <cmpexpr> [ (and | or) <boolexpr> ]
BoolExpr* SyntaticAnalysis::procBoolExpr() {
    bool negative = false;

    if (m_current.type == TKN_NOT) {
        negative = true;
        advance();
    }

    BoolExpr* c;
    if(negative) c = new NotBoolExpr(m_lex.line(), procCmpExpr());
    else c = procCmpExpr();

    if (m_current.type == TKN_AND || m_current.type == TKN_OR){
        CompositeBoolExpr::BoolOp op;

        switch(m_current.type){
            case TKN_AND:
                op = CompositeBoolExpr::And;
                break;

            case TKN_OR:
                op = CompositeBoolExpr::Or;
                break;

            default: break;
        }

        advance();
        BoolExpr* expr_2 = procBoolExpr();

        c = new CompositeBoolExpr(m_lex.line(), c, op, expr_2);
    }

    return c;
}

// <cmpexpr>  ::= <expr> ('=' | '<>' | '<' | '>' | '<=' | '>=') <expr> |
//            '(' <expr> ('=' | '<>' | '<' | '>' | '<=' | '>=') <expr> ')'
SingleBoolExpr* SyntaticAnalysis::procCmpExpr() {
    bool existPar = m_current.type == TKN_OPEN_PAR;

    if (existPar) eat(TKN_OPEN_PAR);

    Expr* expr_1 = procExpr();

    enum SingleBoolExpr::RelOp op;

    switch (m_current.type){
        case TKN_EQUAL:
            op = SingleBoolExpr::EQUAL;
            advance();
            break;

        case TKN_NOT_EQUAL:
            op = SingleBoolExpr::NOT_EQUAL;
            advance();
            break;

        case TKN_LOWER:
            op = SingleBoolExpr::LOWER;
            advance();
            break;

        case TKN_GREATER:
            op = SingleBoolExpr::GREATER;
            advance();
            break;

        case TKN_LOWER_EQ:
            op = SingleBoolExpr::LOWER_EQUAL;
            advance();
            break;

        case TKN_GREATER_EQ:
            op = SingleBoolExpr::GREATER_EQUAL;
            advance();
            break;

        default: showError();
    }

    Expr* expr_2 = procExpr();

    SingleBoolExpr* c = new SingleBoolExpr(m_lex.line(), expr_1, op, expr_2);

    if (existPar) eat(TKN_CLOSE_PAR);

    return c;
}

// <expr>     ::= <term> { ('+' | '-') <term> }
Expr* SyntaticAnalysis::procExpr() {
    Expr* c = procTerm();

    while ((m_current.type == TKN_ADD) || (m_current.type == TKN_SUB)) {
        BinaryExpr::BinaryOp op;

        switch(m_current.type){
            case TKN_ADD:
                op = BinaryExpr::AddOp;
                break;
            case TKN_SUB:
                op = BinaryExpr::SubOp;
                break;
            default: break;
        }
        advance();

        Expr* second = procTerm();
        c = new BinaryExpr(m_lex.line(), c, op, second);
    }

    return c;
}

// Situação da linguagem, provávelmente a atribuição de uma variável à outra
// irá conectar os "ponteiros" das duas, esse seria o comportamente desejado?
// <term>     ::= <factor> { ('*' | '/' | '%') <factor> }
Expr* SyntaticAnalysis::procTerm() {
    Expr* c = procFactor();

    while ((m_current.type == TKN_MUL) || (m_current.type == TKN_DIV) || (m_current.type == TKN_MOD)) {
        int op;

        switch(m_current.type){
            case TKN_MUL:
                op = BinaryExpr::MulOp;
                break;
            
            case TKN_DIV:
                op = BinaryExpr::DivOp;
                break;

            case TKN_MOD:
                op = BinaryExpr::ModOp;
                break;

            default: break;
        }
        advance();
        Expr* second = procFactor();

        c = new BinaryExpr(m_lex.line(), c, BinaryExpr::MulOp, second);
    }
    
    return c;
}

// <factor>   ::= <value> | <id> | '(' <expr> ')'
Expr* SyntaticAnalysis::procFactor() {
    Expr* c;

    switch(m_current.type){
        case TKN_INTEGER:
        case TKN_REAL:
        case TKN_STRING:
            c = new ConstExpr(m_lex.line() ,procValue());
            break;

        case TKN_ID:
            c = procId();
            break;

        default:
            eat(TKN_OPEN_PAR);
            c = procExpr();
            eat(TKN_CLOSE_PAR);
    }

    return c;
}

// <value>    ::= <integer> | <real> | <string>
Type* SyntaticAnalysis::procValue() {
    switch(m_current.type){
        case TKN_INTEGER:
            return procInteger();

        case TKN_REAL:
            return procReal();
        
        case TKN_STRING:
            return procString();
        
        default: showError();
    }
}

Variable* SyntaticAnalysis::procId() {
    // implementar leitura e escrita em Variable na memória
    Variable* c = new Variable(m_lex.line() ,m_current.token.c_str());
    eat(TKN_ID);
    return c;
}

IntegerValue* SyntaticAnalysis::procInteger() {
    std::string tmp = m_current.token;

    eat(TKN_INTEGER);

    IntegerValue* value = new IntegerValue(atoi(tmp.c_str()));

    return value;
}

RealValue* SyntaticAnalysis::procReal() {
    std::string tmp = m_current.token;

    eat(TKN_REAL);

    RealValue* value = new RealValue(std::stod(tmp.c_str()));

    return value;
}

StringValue* SyntaticAnalysis::procString() {
    std::string tmp = m_current.token;

    eat(TKN_STRING);

    StringValue* value = new StringValue(tmp.c_str());

    return value;
}
