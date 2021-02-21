#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include <list>
#include "Command.h"
#include "../expression/Expr.h"

class Expr;

class WriteCommand : public Command{
    public:
        WriteCommand(int line, bool writeln = 0);
        virtual ~WriteCommand();

        void addExpr(Expr* expr);
        virtual void execute();
    
    private:
        std::list<Expr*> m_exprs;
        bool m_writeln;

};

#endif