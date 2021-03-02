#include "SingleBoolExpr.h"

SingleBoolExpr::SingleBoolExpr(int line, Expr* left, enum SingleBoolExpr::RelOp op, Expr* right)
	: BoolExpr(line), m_left(left), m_op(op), m_right(right) {
}

SingleBoolExpr::~SingleBoolExpr() {
	delete m_left;
	delete m_right;
}

bool SingleBoolExpr::expr() {
	//Tem que fazer o cast ainda se isso n funcionar
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

	switch (m_op) {
		case SingleBoolExpr::EQUAL:
			return v1 == v2;
		case SingleBoolExpr::NOT_EQUAL:
			return v1 != v2;
		case SingleBoolExpr::LOWER:
			return v1 < v2;
		case SingleBoolExpr::LOWER_EQUAL:
			return v1 <= v2;
		case SingleBoolExpr::GREATER:
			return v1 > v2;
		case SingleBoolExpr::GREATER_EQUAL:
		default:
			return v1 >= v2;
	}
}