

#pragma once
#include <DxLib.h>
#include "Math.h"
#include "ModeBase.h"

class Actor;
class Game;

class LightBase  {
	public:
		struct Parameter {
			Vector2 pos;
			int _rotation;
			Vector2 _scale;
		};

		LightBase(Game& game,ModeBase& mode,Actor& owner);
		void Update();
		Parameter GetParameter();
		

	private:

		Actor& _owner;
		Vector2 _pos;
		int _rotation;
		Vector2 _scale;

};

