#include "ForCommand.h"
#include "../expression/Expr.h"
#include "../expression/Variable.h"

ForCommand::ForCommand(int line, Variable* var, Expr* src, Expr* dst, Command* cmd)
    :Command(line),m_var(var),m_src(src),m_cmd(cmd){
}

ForCommand::~ForCommand(){
    delete m_var;
    delete m_src;
    delete m_dst;
    delete m_cmd;
}

void ForCommand::execute(){
    // Tem que implementar
}