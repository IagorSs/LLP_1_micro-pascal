#include "Variable.h"

Variable::Variable(int line, std::string name)
    :Expr(line), m_name(name){
}

Variable::~Variable(){
}

void Variable::setValue(Type* value) {
	if(isConst()) Memory::registryConstant(m_name, value);
	else Memory::registryVariable(m_name, value);
}

void Variable::setConst(){
	m_isConst = true;
}

Type* Variable::expr() {
	return Memory::read(m_name);
}

bool Variable::isConst() {
	return m_isConst;
}