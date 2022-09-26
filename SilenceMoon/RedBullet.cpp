/*****************************************************************//**
 * \file   Bullet.h
 * \brief  �v���C���[�����˂���Ԃ��e�e
 *
 * \author amg
 * \date   July 2022
 *********************************************************************/
#include "RedBullet.h"
#include "ModeGame.h"
#include "FX_BulletHit.h"

RedBullet:: RedBullet(Game& game, ModeGame& mode, Vector2 pos, double dir)
	:Bullet(game,mode,pos,dir)
{
	_cg = ImageServer::LoadGraph("resource/Bullet/Bullet_1.png");
}

void RedBullet::Dead() {
	Bullet::Dead();
	_mode.GetActorServer().Add(std::make_unique<FX_BulletHitRed>(_game, _mode, _pos, _game.GetFrameCount()));
}
