#include "IfCommand.h"

IfCommand::IfCommand(int line, BoolExpr* cond, Command* thenCmds, Command* elseCommands)
    : Command(line), m_cond(cond), m_thenCmds(thenCmds),m_elseCmds(elseCommands){
}

IfCommand::IfCommand(int line, BoolExpr* cond, Command* thenCmds)
    : Command(line), m_cond(cond), m_thenCmds(thenCmds){
}

IfCommand:: ~IfCommand(){
    delete m_cond;
    delete m_thenCmds;
    if(m_elseCmds) delete m_elseCmds;
}

void IfCommand::setElseCommands(Command* elseCmds){
    m_elseCmds = elseCmds;
}

void IfCommand:: execute(){
    if (m_cond->expr()) m_thenCmds->execute();
    else if (m_elseCmds) m_elseCmds->execute();
}