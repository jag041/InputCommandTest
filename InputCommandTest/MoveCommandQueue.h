#pragma once

// std includes
#include <iostream>

// my includes
#include "GlobalConsts.h"
#include "PoolAllocator.h"
#include "MoveCommand.h"

class MoveCommandQueue {
public:
	MoveCommandQueue(PoolAllocator<MoveCommand>* new_pool);
	// can enqueue up to MAX_MOVES commands, throws an error currently if more than 8 are enqueued
	void add_command(MoveCommand* cmd);
	// executes enqueued commands in order and removes them from the memory pool
	void execute_commands();

	void clear_commands();

private:
	// memory pool to control memory allocations
	PoolAllocator<MoveCommand>* command_pool;
	
	// handles into command_pool
	size_t commands[MAX_MOVES];

	// total number of commands prior to execution
	size_t num_commands{ 0 };

};