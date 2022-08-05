#pragma once
#include "Actor.h"
#include <vector>

class Switch :public Actor{
public:
	Switch(Game& game, ModeGame& mode);

	void Update()override;
	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

private:

	std::vector<Actor*> _linkGimmiks;
};
