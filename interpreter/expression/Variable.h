#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "Expr.h"
#include "../value/Value.h"

class Variable : public Expr {
	public:
		Variable(int line, const std::string& name);
		virtual ~Variable();

		const std::string& name() const { return m_name; }
		Type* value();
        void setValue(Type* value);

		virtual Type* expr();

	private:
		const std::string m_name;
};

#endif