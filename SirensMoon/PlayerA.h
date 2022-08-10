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

	/**
	 * @brief ”­Ë‚·‚é’eí‚ğ•Ô‚·
	 * 
	 * \return GreenBullet‚ª€”õ‚³‚ê‚Ä‚¢‚ê‚ÎTrue
	 */
	bool GetBulletType() { return _setGreenBullet; }

private:
	bool _setGreenBullet;
};