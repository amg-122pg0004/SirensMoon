#pragma once
#include <DxLib.h>
#include "Actor.h"
#include "Game.h"

class Light :public Actor {
	public:
		Light(Game& game,Vector2 pos);
		Type GetType() override { return Type::Light; }

		void Update() override;
		

	private:
		int _lifetime;//ライトが継続するフレーム数
};
