#include "ReadCommand.h"

ReadCommand::ReadCommand(int line)
    : Command(line){
}

ReadCommand::~ReadCommand() {
    for (std::list<Variable*>::iterator it = m_vars.begin(),
        ed = m_vars.end(); it != ed; it++) {
        Command* var = *it;
        delete var;
    }
}

void ReadCommand::addVariable(Variable* var){
    m_vars.push_back(var);
}

void ReadCommand::execute(){
    for (std::list<Variable*>::iterator it = m_vars.begin(),
	    ed = m_vars.end(); it != ed; it++) {
		Variable* var = *it;
	}
}