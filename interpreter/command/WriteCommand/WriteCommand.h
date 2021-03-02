#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include <list>
#include <iostream>
#include "../Command.h"
#include "../../expression/Expr/Expr.h"

#include "../../value/IntegerValue/IntegerValue.h"
#include "../../value/StringValue/StringValue.h"
#include "../../value/RealValue/RealValue.h"

class WriteCommand : public Command{
    public:
        WriteCommand(int line, bool writeln);
        virtual ~WriteCommand();

        void addExpr(Expr* expr);
        virtual void execute();
    
    private:
        std::list<Expr*> m_exprs;
        bool m_writeln;

};

#endif