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
		/*1è„,2âE,3â∫,4ç∂*/
		int _dir;

		int _cg_up;
		int _cg_right;
		int _cg_down;
		int _cg_left;

		AABB _accessArea;
};
