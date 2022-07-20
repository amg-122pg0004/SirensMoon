#include "BulletItem.h"
#include "ImageServer.h"

BulletItem::BulletItem(Game& game, ModeBase& mode,Vector2 pos)
	:Actor(game,mode)
{
	_cg = ImageServer::LoadGraph("resource/Item/Ammo.png");
	_pos = pos;
}

void BulletItem::Update() {

}
