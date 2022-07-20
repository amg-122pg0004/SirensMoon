#pragma once
#include "Actor.h"
#include "Math.h"

class Game;
class ModeBase;


class HPItem :public Actor {
public:
	HPItem(Game& game, ModeBase& mode,Vector2 pos);
	void Update()override;
	Type GetType() { return Type::Item; }
	//void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
private:

};