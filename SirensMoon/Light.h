#pragma once
#include <DxLib.h>
#include "Actor.h"
#include "Game.h"
#include "Math.h"

class Light1 :public Actor {
	public:
		Light1(Game& game,Actor& owner);
		Type GetType() override { return Type::Light1; }

		void Update();
		

	private:
		//int _lifetime;//���C�g���p������t���[����
		Actor& _owner;

};
class Light2 :public Actor {
public:
	Light2(Game& game, Actor& owner);
	Type GetType() override { return Type::Light2; }

	void Update();


private:
	//int _lifetime;//���C�g���p������t���[����
	Actor& _owner;

};
