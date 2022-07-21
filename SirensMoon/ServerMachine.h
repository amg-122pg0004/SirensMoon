#pragma once
#include "Actor.h"

class Game;
class ModeBase;

class ServerMachine:public Actor{
	public:
		ServerMachine(Game& game, ModeBase& mode, Vector2 pos,int dir);
		Type GetType() { return Type::Server; }
		void Update()override;
	private:
		/*1��,2�E,3��,4��*/
		int _dir;

		int _cg_up;
		int _cg_right;
		int _cg_down;
		int _cg_left;

		AABB _accessArea;
};
