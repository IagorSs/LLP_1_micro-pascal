#include "CompositeBoolExpr.h"

CompositeExpr::CompositeExpr(int line, BoolExpr* left, enum BoolOp op, BoolExpr* right)
    :BoolExpr(line),m_left(left),m_op(op),m_right(right){
}

CompositeExpr::~CompositeExpr(){
    delete m_left;
    delete m_right;
}

int CompositeExpr::getLine(){
    //Tem que implementar
    
}

bool CompositeExpr::expr(){
    //Tem que implementar
}