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

	/**
	 * @brief ���˂���e���Ԃ�
	 * 
	 * \return GreenBullet����������Ă����True
	 */
	bool GetBulletType() { return _setGreenBullet; }

private:
	bool _setGreenBullet;
};