#pragma once
#include "Player.h"

class PlayerB :public Player{
public:
	PlayerB(Game& game, ModeGame& base, int playernum);
	Actor::Type GetType() override { return Actor::Type::PlayerB; }
	/*�摜�����[�h����*/
	void Load();

	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) override;

	/**/
	void Move() override;

	/*�~�j�}�b�v���J��*/
	void Action() override;
};
