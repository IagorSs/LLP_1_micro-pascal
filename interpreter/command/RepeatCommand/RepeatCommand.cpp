#include "RepeatCommand.h"

RepeatCommand::RepeatCommand(int line, Command* cmds, BoolExpr* cond)
    : Command(line),m_cmds(cmds),m_cond(cond){
}

RepeatCommand::~RepeatCommand(){
    delete m_cmds;
    delete m_cond;
}

void RepeatCommand::execute(){
    // Tem que implementar
    do {
        m_cmds->execute();
    } while (!this->m_cond->expr());
    
}