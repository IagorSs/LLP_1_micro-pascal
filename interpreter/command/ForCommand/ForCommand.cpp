#include "ForCommand.h"

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
    m_var->setValue(m_src->expr());

    IntegerValue* i = (IntegerValue*) m_var->expr();

    while(i <= m_dst->expr()){
        m_cmd->execute();
        i->setValue(i->value() + 1);
    }

    m_var->setValue(i);
}