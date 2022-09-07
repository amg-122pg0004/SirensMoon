#include "BreakableObject.h"
#include "ModeGame.h"

BreakableObject::BreakableObject(Game& game, ModeGame& mode, BreakableObjectData data)
	:Gimmick(game,mode,data.ID)
{
	_pos = data.pos;
	_cg = ImageServer::LoadGraph("resource/Gimmick/breakable.png");
	_size = { 30,90 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
}

void BreakableObject::Update(){
	for (auto&& actor : _mode.GetObjects()) {
		if(actor->GetType() == Type::RedBullet|| actor->GetType() == Type::GreenBullet){
			if(Intersect(_collision, actor->GetCollision())) {
				actor->Dead();
				_dead = true;
			}
		}
	}
}

void BreakableObject::StandardRender(Vector2 window_pos, Vector2 camera_pos)
{
	DrawGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x -10),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y-10),
		_cg,1
	);
}
