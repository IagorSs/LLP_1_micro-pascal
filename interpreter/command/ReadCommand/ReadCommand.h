#ifndef READ_COMMAND_H
#define READ_COMMAND_H

#include <list>
#include "../Command.h"
#include "../../expression/Expr/Variable/Variable.h"

#include "../../value/IntegerValue/IntegerValue.h"
#include "../../value/StringValue/StringValue.h"
#include "../../value/RealValue/RealValue.h"

class ReadCommand: public Command {
    public:
        ReadCommand(int line);
        virtual ~ReadCommand();

        void addVariable(Variable* var);
        virtual void execute();

    private:
        std::list<Variable*> m_vars;
};

#endif