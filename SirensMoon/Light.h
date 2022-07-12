#pragma once
#include <DxLib.h>
#include "Math.h"
#include "ModeBase.h"

class Actor;
class Game;

class Light1 :public Actor {
	public:
		Light1(Game& game,ModeBase& mode,Actor& owner);
		Type GetType() override { return Type::Light1; }

		void Update();
		
	private:
		Actor& _owner;

};
class Light2 :public Actor {
public:
	Light2(Game& game, ModeBase& mode, Actor& owner);
	Type GetType() override { return Type::Light2; }

	void Update();

private:
	Actor& _owner;

};
