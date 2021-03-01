#include "./CaseOption.h"

CaseOption::CaseOption(Type* value, Command* cmd)
  :m_value(value), m_cmd(cmd){};

CaseOption::~CaseOption(){
  delete m_cmd;
  delete m_value;
};