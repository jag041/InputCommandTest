#include "MoveCommandQueue.h"

MoveCommandQueue::MoveCommandQueue(PoolAllocator<MoveCommand>* new_pool) : command_pool(new_pool) {}


void MoveCommandQueue::add_command(MoveCommand* cmd) {

	if (num_commands == MAX_MOVES) {
		throw ErrorHandler("ERROR: Too many commands!!");		// maybe??
		return;
	}

	commands[num_commands] = command_pool->set_data(cmd);
#ifndef N_DEBUG
	std::cout << "command index: " << commands[num_commands] << std::endl;
#endif
	auto ref = command_pool->get_data(commands[num_commands]);
#ifndef N_DEBUG
	std::cout << "command ref: " << ref << std::endl;
	print_command_data(ref);
#endif
	num_commands++;
#ifndef N_DEBUG
	std::cout << "num commands: " << num_commands << std::endl;
#endif
}

void MoveCommandQueue::execute_commands() {

	if (num_commands <= 0)
	{
		std::cout << "no commands to execute" << std::endl;
		return;
	}

	for (size_t i = 0; i < num_commands; ++i) {
		std::cout << "executing command " << i << std::endl;

		size_t index = commands[i];

		auto cmd = command_pool->get_data(index);
#ifndef N_DEBUG
		std::cout << "executing at: " << index << std::endl;
		print_command_data(cmd);
#endif
		cmd->execute();
#ifndef N_DEBUG
		std::cout << "deleteing at: " << index << std::endl;
#endif
		command_pool->delete_data(index);
	}
#ifndef N_DEBUG
	std::cout << "setting num commands to 0" << std::endl;
#endif
	num_commands = 0;
}

void MoveCommandQueue::clear_commands() {
	num_commands = 0;
	command_pool->clear_data();
}

