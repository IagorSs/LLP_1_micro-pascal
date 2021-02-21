#ifndef READ_COMMAND_H
#define READ_COMMAND_H

#include <list>
#include "Command.h"
#include "../expression/Variable.h"

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