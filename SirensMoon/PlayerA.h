#pragma once
#include "Player.h"

class PlayerA :public Player {
public:
	PlayerA(Game& game, ModeGame& base, int playernum);
	Actor::Type GetType() override { return Actor::Type::PlayerA; }
	/*�摜�����[�h����*/
	void Load();

	/*�e������*/
	void Action() override;

private:
	bool _setGreenBullet;
};