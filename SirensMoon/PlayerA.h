#pragma once
#include "Player.h"

class PlayerA :public Player {
public:
	PlayerA(Game& game, ModeBase& base, int playernum);
	Type GetType() override { return Type::PlayerA; }
	/*‰æ‘œ‚ğƒ[ƒh‚·‚é*/
	void Load();

	/*e‚ğŒ‚‚Â*/
	void Action() override;
};