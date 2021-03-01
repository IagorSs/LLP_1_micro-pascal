#ifndef CASE_OPTION_COMMAND_H
#define CASE_OPTION_COMMAND_H

#include <list>
#include "../../Command.h"
#include "../../../value/Type.h"

class CaseOption {
  public:
    Type* m_value;
    Command* m_cmd;

    CaseOption(Type* value, Command* cmd);
    virtual ~CaseOption();
};

#endif
