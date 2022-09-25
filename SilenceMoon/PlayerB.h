#pragma once
#include "Player.h"

class PlayerB :public Player{
public:
	PlayerB(Game& game, ModeGame& base, int playernum);
	Actor::Type GetType() override { return Actor::Type::PlayerB; }
	/*画像をロードする*/
	void Load();

	void StandardRender(Vector2 window_pos, Vector2 camera_pos) override;

	/*ミニマップを開く*/
	void Action() override;
	
	void AnimUpdate()override;

	void TeleportEvent()override;
};
