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
		//int _lifetime;//ライトが継続するフレーム数
		Actor& _owner;
};
