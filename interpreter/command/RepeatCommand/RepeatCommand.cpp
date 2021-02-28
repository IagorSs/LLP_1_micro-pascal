#include "RepeatCommand.h"

RepeatCommand::RepeatCommand(int line, std::list<Command*> cmds, BoolExpr* cond)
    : Command(line),m_cmds(cmds),m_cond(cond){
}

RepeatCommand::~RepeatCommand(){
    for (std::list<Command*>::iterator it = m_cmds.begin(),
	     ed = m_cmds.end(); it != ed; it++) {
             Command* cmds = *it;
             delete cmds;
    }
    delete m_cond;
}

void RepeatCommand::execute(){
    // Tem que implementar
}