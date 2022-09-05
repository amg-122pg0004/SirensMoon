#include "ScreenPump.h"
#include "ModeGame.h"
#include "Player.h"
#include "Enemy.h"

ScreenPump::ScreenPump(Game& game, ModeGame& mode, ObjectDataStructs::ScreenPumpData data)
	:Gimmick(game, mode, data.ID), _dir{ data.dir }
{
	_range = data.range;
	_pos = data.pos;
	_size = { 30,30 };
	_collision.min = { 0,0 };
	_collision.max = { 0,0 };

	switch (data.dir) {
	case 1:
		_detectionArea.min = _pos;
		_detectionArea.max = { _pos.x + _size.x + _range ,_pos.y + _size.y };
		_cg.first = ImageServer::LoadGraph("resource/Gimmick/Screen/right_a.png");
		_cg.second= ImageServer::LoadGraph("resource/Gimmick/Screen/right_p.png");
		break;
	case 2:
		_detectionArea.min = _pos;
		_detectionArea.max = { _pos.x + _size.x,_pos.y + _size.y + _range };
		_cg.first = ImageServer::LoadGraph("resource/Gimmick/Screen/down_a.png");
		_cg.second = ImageServer::LoadGraph("resource/Gimmick/Screen/down_p.png");
		break;
	case 3:
		_detectionArea.min = { _pos.x - _range,_pos.y };
		_detectionArea.max = { _pos.x + _size.x , _pos.y + _size.y };
		_cg.first = ImageServer::LoadGraph("resource/Gimmick/Screen/left_a.png");
		_cg.second = ImageServer::LoadGraph("resource/Gimmick/Screen/left_p.png");
		break;
	case 4:
		_detectionArea.min = { _pos.x , _pos.y - _range };
		_detectionArea.max = { _pos.x + _size.x , _pos.y + _size.y };
		_cg.first = ImageServer::LoadGraph("resource/Gimmick/Screen/up_a.png");
		_cg.second = ImageServer::LoadGraph("resource/Gimmick/Screen/up_p.png");
		break;
	default:
		_detectionArea.min = _pos;
		_detectionArea.max = _pos + _size;
		break;
	}

}

void ScreenPump::Update() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA ) {
			if (Intersect(_detectionArea, actor->GetCollision())) {
				if (dynamic_cast<Player&>(*actor).SetHideFlag()) {
					_mode.GetSplitWindow()[1]->ScreenPumpEvent();
					PlaySoundMem(SoundServer::Find("MicroBomRelease"), DX_PLAYTYPE_BACK);
				}
			}
		}
		if (actor->GetType() == Type::PlayerB) {
			if (Intersect(_detectionArea, actor->GetCollision())) {
				if (dynamic_cast<Player&>(*actor).SetHideFlag()) {
					_mode.GetSplitWindow()[0]->ScreenPumpEvent();
					PlaySoundMem(SoundServer::Find("MicroBomRelease"), DX_PLAYTYPE_BACK);
				}
			}
		}
	}
}

void ScreenPump::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	/*
	double angle{ (_dir - 1) * 3.1415 / 2 };

	DrawRotaGraph(static_cast<int>(_pos.x + (_size.x / 2) + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + (_size.y / 2) + window_pos.y - camera_pos.y)
		, 1.0
		, angle
		, _cg
		, 1);
		*/
	int cg{ -1 };
	if (_game.GetFrameCount() % 60 < 30) {
		cg = _cg.first;
	}
	else {
		cg = _cg.second;
	}
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, cg
		, 1);
}

void ScreenPump::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_detectionArea.Draw2(window_pos, camera_pos);
}