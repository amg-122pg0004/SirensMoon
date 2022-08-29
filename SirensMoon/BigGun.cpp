#include "BigGun.h"
#include "ModeGame.h"

BigGun::BigGun(Game& game, ModeGame& mode, ObjectDataStructs::BigGunData data)
	:Gimmick(game,mode,data.ID),_accessible{false}
{
	_cg = ImageServer::LoadGraph("resource/Gimmick/biggun.png");
	_pos = data.pos;
	_size = { 600, 600 };
	_collision.min = _pos;
	_collision.max = _pos + _size;

}

void BigGun::Update(){
	if (_accessible) {
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Type::PlayerA) {
				if (Intersect(_accessArea, actor->GetCollision())) {
					if(_game.GetInputManager()->CheckInput("ACCESS", 't', 1)) {
						dynamic_cast<Player&>(*actor).ChangeMovable(false);
					}
				}
			}
		}
	}
}
void BigGun::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, static_cast<int>(_pos.x + window_pos.x - camera_pos.x+_size.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y+_size.y)
		, _cg
		, 1);
}


