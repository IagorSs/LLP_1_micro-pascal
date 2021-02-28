#include "Variable.h"
#include "../util/Memory.h"

Variable::Variable(int line, const std::string& name)
    :Expr(line), m_name(name){
}

Variable::~Variable(){
}

Type* Variable::value() {
	return Memory::read(m_name);
}

void Variable::setValue(Type* value) {
	Memory::write(m_name, value);
}

Type* Variable::expr() {
	return this->expr();
}