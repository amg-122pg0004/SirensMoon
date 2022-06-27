#pragma once
#include <DxLib.h>
#include "Actor.h"

class Player :public Actor {
	public:
		Player(Game& game,int playernum);
		void Update() override ;
		void Render() override;

	private:
		std::shared_ptr<InputManager> _inputManager;

		int _speed;
		int _playerNum;

		int _cg_up;
		int _cg_side;
		int _cg_down;



		enum class State {
			UP,DOWN,LEFT,RIGHT
		};

		State _state;
};
