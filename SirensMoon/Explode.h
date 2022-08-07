#pragma once
#include "Actor.h"

class Game;
class ModeGame;

class Explode :public Actor {
public:
	Explode(Game& game,ModeGame& mode,Vector2 pos);
	void Update();
	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) override;
	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

	Type GetType()override { return Type::Explode; }

private:
	int _lifetime;
};
