#pragma once
#include <DxLib.h>
#include "Game.h"
#include "Math.h"

class Actor;

class Light1 :public Actor {
	public:
		Light1(Game& game,Actor& owner);
		Type GetType() override { return Type::Light1; }

		void Update();
		
	private:
		Actor& _owner;

};
class Light2 :public Actor {
public:
	Light2(Game& game, Actor& owner);
	Type GetType() override { return Type::Light2; }

	void Update();

private:
	Actor& _owner;

};
