#ifndef REPEAT_COMMAND_H
#define REPEAT_COMMAND_H

#include <list>
#include "Command.h"
#include "../expression/BoolExpr.h"

class BoolExpr;

class RepeatCommand : public Command{
    public:
        RepeatCommand(int line, std::list<Command*> cmds, BoolExpr* cond);
        virtual ~RepeatCommand();

        virtual void execute();

    private:
        std::list<Command*> m_cmds;
        BoolExpr* m_cond;
};

#endif