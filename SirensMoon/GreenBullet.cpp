#include "GreenBullet.h"
#include "ModeGame.h"
#include "FX_BulletHit.h"

GreenBullet::GreenBullet(Game& game, ModeGame& mode, Vector2 pos, double dir)
	:Bullet(game, mode, pos, dir)
{
	_cg = ImageServer::LoadGraph("resource/Bullet/Bullet_2.png");
}

void GreenBullet::Dead() {
	Actor::Dead();
	_mode.GetActorServer().Add(std::make_unique<FX_BulletHitGreen>(_game, _mode, _pos, _game.GetFrameCount()));
}