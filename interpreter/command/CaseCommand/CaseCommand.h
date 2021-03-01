#ifndef CASE_COMMAND_H
#define CASE_COMMAND_H

#include <list>
#include "../Command.h"
#include "../../expression/Expr/Expr.h"
#include "./CaseOption/CaseOption.h"

class CaseCommand : public Command{
    public:
        CaseCommand(int line, Expr* expr);
        virtual ~CaseCommand();

        virtual void execute();
        virtual void addOption(Type* value, Command* cmd);
        virtual void setOtherwise(Command* cmd);

    private:
        Expr* m_expr;
        std::list<CaseOption*> m_options;
        Command* m_otherwise;
};

#endif