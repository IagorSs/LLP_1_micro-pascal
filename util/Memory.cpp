#include "Memory.h"

std::map<std::string, Type*> m_memory;

Type* read(std::string& name){
    return m_memory[name];
}

void write(std::string& name, Type* value){
    m_memory[name] = value;
}
