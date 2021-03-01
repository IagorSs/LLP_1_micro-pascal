#include "BlocksCommand.h"

BlocksCommand::BlocksCommand(int line)
	: Command(line) {
}

BlocksCommand::~BlocksCommand() {
	for (Command* cmd: m_cmds) {
		delete cmd;
	}
}

void BlocksCommand::addCommand(Command* cmd) {
	m_cmds.push_back(cmd);
}

void BlocksCommand::execute() {
	for (Command* cmd: m_cmds) {
		cmd->execute();
	}
}