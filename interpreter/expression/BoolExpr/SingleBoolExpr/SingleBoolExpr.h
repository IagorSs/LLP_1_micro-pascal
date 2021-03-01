#ifndef SINGLE_BOOL_EXPR_H
#define SINGLE_BOOL_EXPR_H

#include "../BoolExpr.h"
#include "../../Expr/Expr.h"

class SingleBoolExpr : public BoolExpr {
	public:
		enum RelOp {
			EQUAL = 1,
			NOT_EQUAL,
			LOWER,
			GREATER,
			LOWER_EQUAL,
			GREATER_EQUAL
		};

		SingleBoolExpr(int line, Expr* left, enum RelOp op, Expr* right);
		virtual ~SingleBoolExpr();

		virtual int line();
		virtual bool expr();

	private:
		Expr* m_left;
		enum RelOp m_op;
		Expr* m_right;

};

#endif