#pragma once
#include <DxLib.h>
#include "Actor.h"
#include "InputManager.h"
#include "Game.h"
#include "Collision.h"

class Player :public Actor {
	public:
		Player(Game& game,int playernum);
		void Update() override ;
		void Render(Vector2 window_pos,Vector2 camera_pos) override ;

		int IsHitMapChip(int dirX,int dirY);

	private:
		std::shared_ptr<InputManager> _inputManager;

		int _dirX;
		int _dirY;
		int _speed;
		int _playerNum;

		int _cg_up;
		int _cg_side;
		int _cg_down;



		enum class State {
			UP,DOWN,LEFT,RIGHT
		};

		State _state;
		AABB _collision;
};
