#pragma once
#include <DxLib.h>
#include "Actor.h"
#include "Game.h"
#include "Math.h"

class Light :public Actor {
	public:
		Light(Game& game,Actor& owner);
		Type GetType() override { return Type::Light; }

		void Update();
		

	private:
		//int _lifetime;//���C�g���p������t���[����
		Actor& _owner;
};
