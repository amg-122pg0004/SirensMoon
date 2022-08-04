#pragma once
#include "Player.h"

class PlayerA :public Player {
public:
	PlayerA(Game& game, ModeGame& base, int playernum);
	Actor::Type GetType() override { return Actor::Type::PlayerA; }
	/*画像をロードする*/
	void Load();

	/*銃を撃つ*/
	void Action() override;
};