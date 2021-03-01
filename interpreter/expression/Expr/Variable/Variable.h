#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "../Expr.h"
#include "../../../../util/Memory.h"

class Variable : public Expr {
	public:
		Variable(int line, std::string name);
		virtual ~Variable();

		std::string name() { return m_name; }
		
		void setValue(Type* value);

		virtual Type* expr();

	private:
		std::string m_name;
};

#endif