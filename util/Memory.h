#ifndef MEMORY_H
#define MEMORY_H

#include <map>
#include <set>
#include <string>
#include "../interpreter/value/Value.h"

class Memory {
	public:
		void registryVariable(const std::string& name, Type* value = NULL);
		void registryConstant(const std::string& name, Type* value);
		Type* read(std::string& name);
		void write(std::string& name, Type* value);

	private:
		static std::map<std::string, Type*> m_memory;
		static std::set<std::string > m_consts;
	
};

#endif  