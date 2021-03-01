#ifndef COMPOSITE_EXPR_H
#define COMPOSITE_EXPR_H

#include "../BoolExpr.h"

class CompositeBoolExpr : public BoolExpr{
    public:
        enum BoolOp{
            And = 1,
            Or
        };

        CompositeBoolExpr(int line, BoolExpr* left, enum BoolOp op, BoolExpr* right);
        virtual ~CompositeBoolExpr();

        virtual int line();
        virtual bool expr();
    
    private:
        BoolExpr* m_left;
        enum BoolOp m_op;
        BoolExpr* m_right;
};

#endif