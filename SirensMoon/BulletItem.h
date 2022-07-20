#pragma once
#include "Actor.h"
#include "Math.h"

class Game;
class ModeBase;

class BulletItem :public Actor {
	public:
		BulletItem(Game& game, ModeBase& mode,Vector2 pos);
		Type GetType() { return Type::Item; }
		void Update()override;
		//void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	private:

};