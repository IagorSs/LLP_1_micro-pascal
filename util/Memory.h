#ifndef MEMORY_H
#define MEMORY_H

#include <map>
#include <string>

class Memory {
	public:
		static Type* read(std::string name){
			return m_memory[name];
		};

		static void write(std::string name, Type* value){
			m_memory[name] = value;
		};

	private:
		static std::map<std::string, Type*> m_memory;

};

#endif