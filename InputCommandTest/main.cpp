#define SDL_MAIN_HANDLED

// std includes
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

// external includes
#include "SDL.h"

// my includes
#include "GlobalConsts.h"
#include "ErrorHandler.h"
#include "PoolAllocator.h"
#include "MoveCommand.h"
#include "MoveCommandQueue.h"





int main() {

	SDL_SetMainReady();

	if (SDL_Init(SDL_INIT_EVENTS) < 0 || SDL_Init(SDL_INIT_VIDEO) < 0) {

		std::cout << "failed to init sdl" << std::endl;

		return 1;
	}

	SDL_Window* const window = SDL_CreateWindow(
		"Input Command Test",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_VULKAN);

	if (!window)
	{
		std::cout << "failed to create window" << std::endl;
		return 1;
	}

	try
	{
		// init memory allocator
		PoolAllocator<MoveCommand> moves_heap(MAX_MOVES);

		// init object which commands act upon
		Position character(0, 0);

		// init command queue
		MoveCommandQueue char_move_queue(&moves_heap);

		// event to store button inputs
		SDL_Event e;
		bool bQuit = false;


		//main loop
		while (!bQuit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e))
			{
				int key = e.key.keysym.sym;

				//close the window when user alt-f4s or clicks the X button	
				if (e.type == SDL_QUIT || key == SDLK_ESCAPE)
				{
					std::cout << "quitting" << std::endl;
					bQuit = true;
					break;
				}

				// enqueue commands based on arrow key pressed
				if (e.type == SDL_KEYDOWN)
				{
#ifndef N_DEBUG
					std::cout << "button press detected" << std::endl;
#endif
					if (key == SDLK_UP) {
						MoveCommand input(&character, Position(0, 1));
						char_move_queue.add_command(&input);
					}
					if (key == SDLK_RIGHT) {
						MoveCommand input(&character, Position(1, 0));
						char_move_queue.add_command(&input);
					}
					if (key == SDLK_DOWN) {
						MoveCommand input(&character, Position(0, -1));
						char_move_queue.add_command(&input);
					}
					if (key == SDLK_LEFT) {
						MoveCommand input(&character, Position(-1, 0));
						char_move_queue.add_command(&input);
					}

					// execute commands when e is pressed
					if (key == SDLK_e) {
						char_move_queue.execute_commands();
					}

#ifndef N_DEBUG
					std::cout << "x pos: " << character.x << "y pos: " << character.y << std::endl;
#endif
				}
			}
		}

	}
	catch (ErrorHandler& e)
	{

		std::cout << e.what() << std::endl;

	}

	return 0;
}


// friend functions for debugging
#ifndef N_DEBUG
void print_command_data(MoveCommand* cmd) {

	std::cout << "move x: " << cmd->move.x << std::endl
		<< "move y: " << cmd->move.y << std::endl
		<< "position x: " << cmd->cur_pos->x << std::endl
		<< "position y: " << cmd->cur_pos->y << std::endl;

}
#endif
