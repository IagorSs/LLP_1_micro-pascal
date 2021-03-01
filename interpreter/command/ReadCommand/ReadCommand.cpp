#include "ReadCommand.h"
#include <iostream>

ReadCommand::ReadCommand(int line)
    : Command(line){
}

ReadCommand::~ReadCommand() {
    for (Variable* var: m_vars) {
        delete var;
    }
}

void ReadCommand::addVariable(Variable* var){
    m_vars.push_back(var);
}

// Implementação feita pra ter um valor por linha
void ReadCommand::execute(){
    for (Variable* var:m_vars) {
        std::string input;
        Type* value;

        std::cin >> input;

        // false -> number
        // true -> string
        bool numberOrString = false;

        // false -> integer
        // true -> real
        bool integerOrReal = input.find(".") != std::string::npos;

        for(char c_c : input){
            int c_i = (int) c_c;

            if(isalpha(c_i) || c_c == '_'){
                numberOrString = true;
                break;
            }
        }

        if(numberOrString) value = new StringValue(input);
        else if(integerOrReal) value = new RealValue(std::stod(input.c_str()));
        else value = new IntegerValue(atoi(input.c_str()));

        var->setValue(value);
	}
}