#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"
#include <map>

class Command;

class SyntaticAnalysis {
public:
    explicit SyntaticAnalysis(LexicalAnalysis& lex);
    virtual ~SyntaticAnalysis();

    Command* start();

private:
    LexicalAnalysis& m_lex;
    Lexeme m_current;

    void advance();
    void eat(enum TokenType type);
    void showError();

    void procProgram();
    void procConst();
    void procVar();
    void procBody();
    void procBlock();
    void procCmd();
    void procAssign();
    void procIf();
    void procCase();
    void procWhile();
    void procRepeat();
    void procFor();
    void procWrite();
    void procRead();
    void procBoolExpr();
    void procCmpExpr();
    void procExpr();
    void procTerm();
    void procFactor();
    void procValue();
    void procId();
    void procInteger();
    void procReal();
    void procString();

};

#endif
