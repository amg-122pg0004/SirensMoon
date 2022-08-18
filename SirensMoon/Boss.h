#pragma once
#include "Actor.h"
#include <map>

class Player;

class Boss :public Actor {
public:
	Boss(Game& game, ModeGame& mode,Player& p1,Player& p2);
	void Update()override;
	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

private:
	enum class State {
		Wait,
		GunAttack1,
		GunAttack2,
		ShootMissile,
		Jump,
		HeadButt,
		TakeDamage
	};

	std::map < State, std::vector<int>> _cg;
	int _animNo;

	Player& _player1;
	Player& _player2;
};
