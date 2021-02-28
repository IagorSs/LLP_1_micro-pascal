#ifndef COMPOSITE_EXPR_H
#define COMPOSITE_EXPR_H

#include "BoolExpr.h"

class CompositeExpr : public BoolExpr{
    public:
        enum BoolOp{
            And,
            Or
        };

        CompositeExpr(int line, BoolExpr* left, enum BoolOp op, BoolExpr* right);
        virtual ~CompositeExpr();

        virtual int line();
        virtual bool expr();
    
    private:
        BoolExpr* m_left;
        enum BoolOp m_op;
        BoolExpr* m_right;
};

#endif