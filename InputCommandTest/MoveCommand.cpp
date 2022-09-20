#include "MoveCommand.h"


MoveCommand::MoveCommand() {
	cur_pos->x = 0;
	cur_pos->y = 0;
};

MoveCommand::MoveCommand(Position* p, Position m) : cur_pos(p), move(m) {}


void MoveCommand::execute() {
	std::cout << "executing move" << std::endl;
	*cur_pos += move;
}

void MoveCommand::undo() { *cur_pos -= move; }