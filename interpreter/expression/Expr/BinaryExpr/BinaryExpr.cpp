#include "BinaryExpr.h"

BinaryExpr::BinaryExpr(int line, Expr* left, enum BinaryExpr::BinaryOp op, Expr* right)
    :Expr(line),m_left(left),m_op(op),m_right(right){
}

BinaryExpr::~BinaryExpr(){
    delete m_left;
    delete m_right;
}

Type* BinaryExpr::expr(){
    //Tem que implementar

    Type* result;
    double resultNumber;

    switch(this->m_op){
        case BinaryOp::AddOp:
            resultNumber = ((RealValue*)m_left->expr())->value() + ((RealValue*)m_right->expr())->value();
            result = new RealValue(resultNumber);
            break;

        case BinaryOp::SubOp:
            resultNumber = ((RealValue*)m_left->expr())->value() - ((RealValue*)m_right->expr())->value();
            result = new RealValue(resultNumber);
            break;

        case BinaryOp::MulOp:
            resultNumber = ((RealValue*)m_left->expr())->value() * ((RealValue*)m_right->expr())->value();
            result = new RealValue(resultNumber);
            break;

        case BinaryOp::DivOp:
            resultNumber = ((RealValue*)m_left->expr())->value() / ((RealValue*)m_right->expr())->value();
            result = new RealValue(resultNumber);
            break;

        case BinaryOp::ModOp:
            resultNumber = ((IntegerValue*)m_left->expr())->value() % ((IntegerValue*)m_right->expr())->value();
            result = new IntegerValue(resultNumber);
            break;
    }

    return result;
}