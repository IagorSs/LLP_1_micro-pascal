#include "CompositeBoolExpr.h"

CompositeBoolExpr::CompositeBoolExpr(int line, BoolExpr* left, enum BoolOp op, BoolExpr* right)
    :BoolExpr(line),m_left(left),m_op(op),m_right(right){
}

CompositeBoolExpr::~CompositeBoolExpr(){
    delete m_left;
    delete m_right;
}

bool CompositeBoolExpr::expr(){
    //Tem que implementar

    bool v1 = this->m_left->expr();
    bool v2 = this->m_right->expr();

    switch (this->m_op) {
        case And:
            return v1 && v2;
        
        case Or:
            return v1 || v2;
    }
}