#ifndef ASSIGN_COMMAND_H
#define ASSIGN_COMMAND_H

#include "../Command.h"
#include "../../expression/Expr/Variable/Variable.h"

class Variable;
class Expr;

class AssignCommand : public Command{
    public:
        AssignCommand(int line, Variable* left, Expr* right);
        virtual ~AssignCommand();

        virtual void execute();
    
    private:
        Variable* m_left;
        Expr* m_right;
};

#endif