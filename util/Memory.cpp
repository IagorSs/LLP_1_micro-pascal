#include "Memory.h"

std::map<std::string, Type*> Memory::m_memory;
std::set<std::string> Memory::m_consts;

Type* Memory::read(const std::string& name) {
	return Memory::m_memory[name];
}

void Memory::write(const std::string& name, Type* value, bool isConst) {
	if(isConst){
		if(m_consts.find(name)==Memory::m_consts.end())
			m_memory[name] = value;
		else
			printf("Não é possível realizar operacao de sobrescrita");
	} else m_memory[name] = value;
}

void Memory::registryConstant(const std::string& name, Type* value){
	write(name, value, true);
	m_consts.insert(name);
}

void Memory::registryVariable(const std::string& name, Type* value){
	write(name, value, false);
}