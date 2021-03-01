#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"

#include "../interpreter/command/Command.h"
#include "../interpreter/command/WriteCommand/WriteCommand.h"
#include "../interpreter/command/ReadCommand/ReadCommand.h"
#include "../interpreter/command/AssignCommand/AssignCommand.h"
#include "../interpreter/command/BlocksCommand/BlocksCommand.h"
#include "../interpreter/command/IfCommand/IfCommand.h"
#include "../interpreter/command/WhileCommand/WhileCommand.h"
#include "../interpreter/command/RepeatCommand/RepeatCommand.h"
#include "../interpreter/command/ForCommand/ForCommand.h"
#include "../interpreter/command/CaseCommand/CaseCommand.h"

#include "../interpreter/value/IntegerValue/IntegerValue.h"

#include "../interpreter/expression/Expr/Expr.h"
#include "../interpreter/expression/Expr/ConstExpr/ConstExpr.h"
#include "../interpreter/expression/Expr/Variable/Variable.h"
#include "../interpreter/expression/Expr/BinaryExpr/BinaryExpr.h"
#include "../interpreter/expression/BoolExpr/SingleBoolExpr/SingleBoolExpr.h"
#include "../interpreter/expression/BoolExpr/NotBoolExpr/NotBoolExpr.h"
#include "../interpreter/expression/BoolExpr/CompositeBoolExpr/CompositeBoolExpr.h"

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

    Command* procProgram();
    AssignCommand* procConst();
    AssignCommand* procVar();
    Command* procBody();
    BlocksCommand* procBlock();
    Command* procCmd();
    AssignCommand* procAssign();
    IfCommand* procIf();
    CaseCommand* procCase();
    WhileCommand* procWhile();
    RepeatCommand* procRepeat();
    ForCommand* procFor();
    WriteCommand* procWrite();
    ReadCommand* procRead();
    BoolExpr* procBoolExpr();
    SingleBoolExpr* procCmpExpr();
    Expr* procExpr();
    Expr* procTerm();
    Expr* procFactor();
    Type* procValue();
    Variable* procId();
    IntegerValue* procInteger();
    RealValue* procReal();
    StringValue* procString();

};

#endif
