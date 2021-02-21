#include "WriteCommand.h"
#include "../expression/Expr.h"

 WriteCommand::WriteCommand(int line, bool writeln = 0)
    :Command(line),m_writeln(writeln){
}

 WriteCommand::~WriteCommand(){
     for (std::list<Expr*>::iterator it = m_exprs.begin(),
	     ed = m_exprs.end(); it != ed; it++) {
		Expr* expr = *it;
		delete expr;
	}
}

void WriteCommand::addExpr(Expr* expr){
    m_exprs.push_back(expr);
}
        
void  WriteCommand::execute(){
    //Tem que implementar
}

