#ifndef REPEAT_COMMAND_H
#define REPEAT_COMMAND_H

#include <list>
#include "../Command.h"
#include "../../expression/BoolExpr/BoolExpr.h"

class RepeatCommand : public Command{
    public:
        RepeatCommand(int line, Command* cmds, BoolExpr* cond);
        virtual ~RepeatCommand();

        virtual void execute();

    private:
        Command* m_cmds;
        BoolExpr* m_cond;
};

#endif