#include "WriteCommand.h"

 WriteCommand::WriteCommand(int line, bool writeln)
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
    for(Expr* current:this->m_exprs){
        switch(current->expr()->type()){
            case Type::IntegerType:
                IntegerValue* valueInt = (IntegerValue*)(current->expr());
                printf("%i", valueInt->value());
                break;

            case Type::RealType:
                RealValue* valueReal = (RealValue*)(current->expr());
                printf("%lf", valueReal->value());
                break;

            case Type::StringType:
                StringValue* valueString = (StringValue*)(current->expr());
                printf("%s", valueString->value());
                break;
        }
    }

    if(this->m_writeln) printf("\n");
}

