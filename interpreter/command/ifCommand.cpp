#include "IfCommand.h"
#include "../expression/BoolExpr.h"

IfCommand::IfCommand(int line, BoolExpr* cond, Command* thenCmds, Command* elseCommand)
    : Command(line), m_cond(cond), m_thenCmds(thenCmds),m_elseCmds(elseCommand){
}

IfCommand:: ~IfCommand(){
    delete m_cond;
    delete m_thenCmds;
    if(m_elseCmds){
        delete m_elseCmds;
    }
}

void IfCommand:: execute(){ 
    if(m_cond->expr())
        m_thenCmds->execute();
    else{
        if (m_elseCmds)
        {
            m_elseCmds->execute();
        }
    }
}