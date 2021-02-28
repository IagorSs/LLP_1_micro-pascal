#include "WriteCommand.h"

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

    for(Expr* current:this->m_exprs){
        switch(current->expr()->type()){
            case Type::IntegerType:
                IntegerValue* value = (IntegerValue*)(current->expr());
                printf("%i", value->value());
                break;

            case Type::RealType:
                RealValue* value = (RealValue*)(current->expr());
                printf("%lf", value->value());
                break;

            case Type::StringType:
                StringValue* value = (StringValue*)(current->expr());
                printf("%s", value->value());
                break;
        }
    }

    if(this->m_writeln) printf("\n");
}

