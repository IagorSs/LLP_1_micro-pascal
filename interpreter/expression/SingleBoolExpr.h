#ifndef SINGLE_BOOL_EXPR_H
#define SINGLE_BOOL_EXPR_H

#include "BoolExpr.h"

class Expr;

class SingleBoolExpr : public BoolExpr {
	public:
		enum Op {
			EQUAL,
			NOT_EQUAL,
			LOWER,
			GREATER,
			LOWER_EQUAL,
			GREATER_EQUAL
		};

		SingleBoolExpr(int line, Expr* left, enum Op op, Expr* right);
		virtual ~SingleBoolExpr();

		virtual bool expr();

	private:
		Expr* m_left;
		enum Op m_op;
		Expr* m_right;

};

#endif