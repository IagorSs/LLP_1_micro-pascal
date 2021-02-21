#ifndef CONST_EXPR_H
#define CONST_EXPR_H

#include "Expr.h"
#include "../value/Value.h"

class ConstExpr : public Expr{
public:
    ConstExpr(int line, Type* Value);
    virtual ~ConstExpr();

    virtual Type* expr();
private:
    Type* m_value;
};

#endif