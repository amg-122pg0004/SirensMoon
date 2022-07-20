#include "HPItem.h"
#include "ImageServer.h"

HPItem::HPItem(Game& game, ModeBase& mode,Vector2 pos)
	:Actor(game, mode)
{
	_cg = ImageServer::LoadGraph("resource/Item/HP.png");
	_pos = pos;
}

void HPItem::Update(){

}
