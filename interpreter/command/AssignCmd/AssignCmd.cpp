#include "AssignCmd.h"
#include "../expression/Variable.h"

AssignCommand::AssignCommand(int line, Variable* left, Expr* rigth)
    : Command(line), m_left(left),m_right(rigth){
}

AssignCommand::~AssignCommand() {
    delete m_left;
    delete m_right;
}

void AssignCommand::execute(){
    Type* value = m_right->expr();
    m_left->setValue(value);
}