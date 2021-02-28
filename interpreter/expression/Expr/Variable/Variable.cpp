#include "Variable.h"

Variable::Variable(int line, std::string name)
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