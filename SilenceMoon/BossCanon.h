/*****************************************************************//**
 * \file   BossCanon.h
 * \brief  �{�X������C�̋ʔ���
 * 
 * \author �y�������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "Actor.h"

class BossCanon :public Actor{
public:
	BossCanon(Game& game, ModeGame& mode, Vector2 pos);
	~BossCanon();
	void Update()override;
	void StandardRender( Vector2 window_pos, Vector2 camera_pos)override;
	void UpdateCollision();

	virtual Type GetType() override { return Type::BossCanon; }
private:
	int _speed;
	int _lifetime;
};
