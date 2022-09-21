#pragma once
#include <iostream>

	//struct Beat {
//
//	int metre = 4;
//	int num = 0;
//
//	int get_beat() const {
//		return num + 1;
//	}
//
//	void update_beat() {
//		++num % metre;
//	}
//};

	struct Position {

		int x = 0;
		int y = 0;

		Position(int nx, int ny) : x(nx), y(ny)
		{}

		void operator+=(Position& rhs)
		{
			x += rhs.x;
			y += rhs.y;
		}

		void operator-=(Position& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
		}
	};



	class MoveCommand {
	public:
		friend void print_command_data(MoveCommand* cmd);

		MoveCommand();
		MoveCommand(Position* p, Position m);

		void execute();

		void undo();
	private:
		Position move{ 0, 0 };
		Position* cur_pos;
	};

	//class MoveUpCommand : public MoveCommand {
	//public:
	//	MoveUpCommand(Position* p) : MoveCommand(p) {};
	//	virtual void execute() {
	//		move.y += 1;
	//		*cur_pos += move;
	//	}
	//
	//	virtual void undo() {
	//		move.y -= 1;
	//		*cur_pos += move;
	//	}
	//};
	//
	//
	//class MoveRightCommand : public MoveCommand {
	//public:
	//	MoveRightCommand(Position* p) : MoveCommand(p) {};
	//
	//	virtual void execute() {
	//		move.x += 1;
	//		*cur_pos += move;
	//	}
	//
	//	virtual void undo() {
	//		move.x -= 1;
	//		*cur_pos += move;
	//	}
	//
	//};
	//
	//class MoveDownCommand : public MoveCommand {
	//public:
	//	MoveDownCommand(Position* p) : MoveCommand(p) {};
	//
	//	virtual void execute() {
	//		std::cout << "executing down command" << std::endl;
	//		move.y -= 1;
	//		*cur_pos += move;
	//	}
	//
	//	virtual void undo() {
	//		move.y += 1;
	//		*cur_pos += move;
	//	}
	//};

	//class MoveLeftCommand : public MoveCommand {
	//public:
	//	MoveLeftCommand(Position* p) : MoveCommand(p) {};
	//
	//	virtual void execute() {
	//		move.x -= 1;
	//		*cur_pos += move;
	//	}
	//
	//	virtual void undo() {
	//		move.x += 1;
	//		*cur_pos += move;
	//	}
	//
	//};


