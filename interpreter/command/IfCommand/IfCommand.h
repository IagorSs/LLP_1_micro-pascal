#ifndef IF_COMMAND_H
#define IF_COMMAND_H

#include "../Command.h"
#include "../../expression/BoolExpr/BoolExpr.h"

class IfCommand : public Command{
    public:
        IfCommand(int line, BoolExpr* cond, Command* thenCmds);
        IfCommand(int line, BoolExpr* cond, Command* thenCmds, Command* elseCommands);
        virtual ~IfCommand();
        
        virtual void setElseCommands(Command* elseCmds);
        virtual void execute();
    
    private:
        BoolExpr* m_cond;
        Command* m_thenCmds;
        Command* m_elseCmds;
};

#endif