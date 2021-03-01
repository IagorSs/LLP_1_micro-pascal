#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H

#include "../Expr.h"

#include "../../../value/RealValue/RealValue.h"
#include "../../../value/IntegerValue/IntegerValue.h"
#include "../../../value/Value.h"

class BinaryExpr : public Expr{
    public:
        enum BinaryOp{
            AddOp = 1,
            SubOp,
            MulOp,
            DivOp,
            ModOp
        };

        BinaryExpr(int line, Expr* left, enum BinaryOp op, Expr* right);
        virtual ~BinaryExpr();

        virtual Type* expr();

    private:
        Expr* m_left;
        enum BinaryOp m_op;
        Expr* m_right;
};

#endif