#pragma once
#include "Player.h"

class PlayerA :public Player {
public:
	PlayerA(Game& game, ModeGame& base, int playernum);
	Actor::Type GetType() override { return Actor::Type::PlayerA; }
	/*‰æ‘œ‚ğƒ[ƒh‚·‚é*/
	void Load();

	/*e‚ğŒ‚‚Â*/
	void Action() override;

private:
	bool _setGreenBullet;
};