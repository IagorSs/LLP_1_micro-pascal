#include "ConstExpr.h" 

ConstExpr::ConstExpr(int line, Type* Value) 
    : Expr(line),m_value(Value){
}

ConstExpr::~ConstExpr(){
}

Type* ConstExpr::expr(){
    return m_value;
}

