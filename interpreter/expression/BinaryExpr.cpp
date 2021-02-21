#include "BinaryExpr.h"
#include "../value/Value.h"

BinaryExpr::BinaryExpr(int line, Expr* left, enum BinaryExpr::BinaryOp op, Expr* right)
    :Expr(line),m_left(left),m_op(op),m_right(right){
}

BinaryExpr::~BinaryExpr(){
    delete m_left;
    delete m_right;
}

Type* BinaryExpr::expr(){
    //Tem que implementar
}