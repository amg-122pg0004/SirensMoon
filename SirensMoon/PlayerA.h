#pragma once
#include "Player.h"

class PlayerA :public Player {
public:
	PlayerA(Game& game, ModeBase& base, int playernum);
	Type GetType() override { return Type::PlayerA; }
	/*画像をロードする*/
	void Load();

	/*銃を撃つ*/
	void Action() override;
};