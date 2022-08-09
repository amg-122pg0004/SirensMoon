#include "GreenBullet.h"
#include "ImageServer.h"

GreenBullet::GreenBullet(Game& game, ModeGame& mode, Vector2 pos, Vector2 dir)
	:Bullet(game, mode, pos, dir)
{
	_cg = ImageServer::LoadGraph("resource/Bullet/Bullet_2.png");
}
