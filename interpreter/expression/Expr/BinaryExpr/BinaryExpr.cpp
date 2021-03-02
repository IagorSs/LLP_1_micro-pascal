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

    Type::ValueType leftType = m_left->expr()->type();
    Type::ValueType rightType = m_right->expr()->type();

    Type* left = m_left->expr();
    Type* right = m_right->expr();

    double v1;
    double v2;
    
    if(leftType == Type::IntegerType) v1 = ((IntegerValue*) left)->value();
    else v1 = ((RealValue*) left)->value();

    if(rightType == Type::IntegerType) v2 = ((IntegerValue*) right)->value();
    else v2 = ((RealValue*) right)->value();

    Type* result;
    double resultNumber;

    switch(this->m_op){
        case BinaryOp::AddOp:
            resultNumber = v1 + v2;
            result = new RealValue(resultNumber);
            break;

        case BinaryOp::SubOp:
            resultNumber = v1 - v2;
            result = new RealValue(resultNumber);
            break;

        case BinaryOp::MulOp:
            resultNumber = v1 * v2;
            result = new RealValue(resultNumber);
            break;

        case BinaryOp::DivOp:
            resultNumber = v1/v2;
            result = new RealValue(resultNumber);
            break;

        case BinaryOp::ModOp:
            resultNumber = (int)v1 % (int)v2;
            result = new IntegerValue(resultNumber);
            break;
    }

    return result;
}