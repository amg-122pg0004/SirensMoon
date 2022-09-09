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

	void AnimUpdate()override;

	int GetAmmo() { return _bullet; }
	int GetCharge() { return _charge; }
	void TakeAmmo();
private:
	bool _setGreenBullet;

	/*�ˌ��֌W*/
	int _bullet;//�c��̒e��
	int _charge;//�`���[�W
	int _cooldown;//�N�[���_�E��
};