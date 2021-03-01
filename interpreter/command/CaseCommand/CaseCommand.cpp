#include "./CaseCommand.h"

CaseCommand::CaseCommand(int line, Expr* expr)
  : Command(line), m_expr(expr){}

CaseCommand::~CaseCommand(){
  for(CaseOption* opt:m_options) delete opt;

  delete m_expr;
  delete m_otherwise;
}

void CaseCommand::addOption(Type* value, Command* cmd){
  CaseOption* co = new CaseOption(value, cmd);

  m_options.push_back(co);
}

void CaseCommand::setOtherwise(Command* cmd){
  m_otherwise = cmd;
}

void CaseCommand::execute(){
  bool dontFind = true;

  for(CaseOption* opt:m_options){
    if(m_expr->expr() == opt->m_value){
      opt->m_cmd->execute();
      dontFind = false;
      break;
    }
  }

  if(dontFind) m_otherwise->execute();
}