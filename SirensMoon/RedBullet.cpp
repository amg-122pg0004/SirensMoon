#include "RedBullet.h"

RedBullet:: RedBullet(Game& game, ModeGame& mode, Vector2 pos, Vector2 dir)
	:Bullet(game,mode,pos,dir)
{
	_cg = ImageServer::LoadGraph("resource/Bullet/Bullet_1.png");
}
