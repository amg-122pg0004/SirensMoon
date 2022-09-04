#include "AimUI.h"
#include "Game.h"
#include "ModeGame.h"
#include "Boss.h"

AimUI::AimUI(Game& game, ModeBase& mode,Vector2 pos,Vector2 size)
	:UIBase(game,mode,pos,size),_speed{2}
{
	_inputManager = _game.GetInputManager();
	_cg = ImageServer::LoadGraph("resource/UI/AimUI/frame.png");
	_cg_cursor = ImageServer::LoadGraph("resource/UI/AimUI/cursor.png");
	_pos_cursor = {930/2,1080/2};
	_visible = true;
}

void AimUI::Update() {
	Vector2 dir =_inputManager->CheckAnalogInput(0);
	if (dir.Length() > 1) {
		dir.Normalize();
	}
		_pos_cursor = _pos_cursor + (dir * _speed);

	if (_pos_cursor.x < 0) {
		_pos_cursor.x = 0;
	}
	if (_pos_cursor.x > splitscreen_W) {
		_pos_cursor.x = splitscreen_W;
	}
	if (_pos_cursor.y < 0) {
		_pos_cursor.y = 0;
	}
	if (_pos_cursor.y > screen_H) {
		_pos_cursor.y = screen_H;
	}

	if(_inputManager->CheckInput("ACTION", 't', 0)) {
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Actor::Type::Boss) {
				AABB col = dynamic_cast<Boss&>(*actor).GetHitBox();
				Vector2 world_pos = _pos + _pos_cursor;
				if (col.min.x < world_pos.x && world_pos.x < col.max.x &&
					col.min.y < world_pos.y && world_pos.y < col.max.y) {
					dynamic_cast<ModeGame&>(_mode).GameClear();
				}
			}
		}
	}
}

void AimUI::Render(){
	if (_visible) {
		DrawRotaGraph(static_cast<int>(_pos_cursor.x), static_cast<int>(_pos_cursor.y), 1.0, 0.0, _cg_cursor, 1);
		DrawGraph(0, 0, _cg, 1);
	}
}