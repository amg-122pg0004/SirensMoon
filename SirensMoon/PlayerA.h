#pragma once
#include "Player.h"

class PlayerA :public Player {
public:
	PlayerA(Game& game, ModeBase& base, int playernum);
	Type GetType() override { return Type::PlayerA; }
	/*�摜�����[�h����*/
	void Load();

	/*�e������*/
	void Action() override;
};