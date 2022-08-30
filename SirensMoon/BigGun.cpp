#include "BigGun.h"
#include "ModeGame.h"
#include "AimUI.h"
#include "BossGimmickController.h"

BigGun::BigGun(Game& game, ModeGame& mode, ObjectDataStructs::BigGunData data, BossGimmickController& controller)
	:Gimmick(game,mode,data.ID),_accessible{false},_controller{controller}
{
	_cg = ImageServer::LoadGraph("resource/Gimmick/biggun.png");
	_pos = data.pos;
	_size = { 600, 600 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	_accessArea.min = { _pos.x,_pos.y + _size.y };
	_accessArea.max = { _pos.x+_size.x,_pos.y + _size.y + 10 };

}

void BigGun::Update(){
	if (_accessible) {
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Type::PlayerA) {
				if (Intersect(_accessArea, actor->GetCollision())) {
					if(_game.GetInputManager()->CheckInput("ACCESS", 't', 0)) {
						dynamic_cast<Player&>(*actor).ChangeMovable(false);
						Vector2 pos =_controller.GetRoomPosition();
						Vector2 size = {splitscreen_W, screen_H};
						Vector2 pos2 = { (pos.x-1) * size.x,(pos.y-1) * size.y };
						pos ={pos.x*size.x,pos.y*size.y};

						_mode.GetSplitWindow()[0]->GetUIServer().emplace_back(std::make_unique<AimUI>(_game, _mode, pos2, size));
						_mode.GetSplitWindow()[0]->GetCamera()->SetPosition(pos);
						_mode.GetSplitWindow()[0]->GetCamera()->SetMovable(false);

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

void BigGun::Debug(Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2(window_pos,camera_pos);
	_accessArea.Draw2(window_pos, camera_pos);
}
