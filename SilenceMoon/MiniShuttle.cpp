/*****************************************************************//**
 * \file   MiniShuttle.cpp
 * \brief  ボス戦で使用するミニシャトルオブジェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "MiniShuttle.h"
#include "ModeGame.h"
#include "BossGimmickController.h"

MiniShuttle::MiniShuttle(Game& game, ModeGame& mode, BossGimmickController& controller, Vector2 pos, bool landing)
	:Gimmick(game, mode, -1), _animNo{ 0 }, _inverse{ false }, _cg2Flag{ false },
	_noCollision{ true }, _controller{ controller }, _landing{ landing },
	_accessible{ false }
{
	_visible = true;
	_cg.resize(100);
	ImageServer::LoadDivGraph("resource/Gimmick/Boss/MiniShuttle.png", 100, 5, 20, 570, 1080, _cg.data());
	_cg2.resize(86);
	ImageServer::LoadDivGraph("resource/Gimmick/Boss/MiniShuttle2.png", 86, 5, 18, 570, 540, _cg2.data());
	_activate = true;
	_pos = pos;
	Vector2 roomPos = CheckRoomPosition();
	_pos = { roomPos.x * splitscreen_W+splitscreen_W / 2, roomPos.y * screen_H +screen_H / 2 };
	_size = { 100,100 };
	Vector2 accessPos = { splitscreen_W / 2 - 8 + roomPos.x * splitscreen_W,screen_H * 0.85 + roomPos.y * screen_H };
	_collisionPreset.min = { accessPos.x - 30,accessPos.y - 30 };
	_collisionPreset.max = { accessPos.x + 30,accessPos.y + 30 };
	_accessArea.min = { accessPos.x - 35,accessPos.y - 30 };
	_accessArea.max = { accessPos.x + 35,accessPos.y + 35 };
	_renderPriority = static_cast<int>(accessPos.y + 30);
}

void MiniShuttle::Debug(Vector2 window_pos, Vector2 camera_pos) {
	DrawBox(static_cast<int>(_pos.x + _size.x / 2 - 5 + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + _size.y / 2 - 5 + window_pos.y - camera_pos.y),
		static_cast<int>(_pos.x + _size.x / 2 + 5 + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + _size.y / 2 + 5 + window_pos.y - camera_pos.y),
		GetColor(255, 255, 0), 1);
	_collision.Draw2(window_pos, camera_pos);
	_accessArea.Draw2(window_pos, camera_pos);
}

void MiniShuttle::Update() {
	if (!_noCollision&&!_landing) {
		if (CheckOverlapAccessArea()) {
			_accessible = true;
		}
	}
	CollisionUpdate();

	if (!_inverse) {
		UpdateAnimation();
	}
	else {
		UpdateInverseAnimation();
	}
}

void MiniShuttle::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	int cg{ -1 };
	if (!_cg2Flag) {
		cg = _cg[_animNo];
	}
	else {
		cg = _cg2[_animNo];
	}
	DrawRotaGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, 1.0, 0.0, cg
		, 1, 0);
}

bool MiniShuttle::CheckOverlapAccessArea() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA) {
			if (Intersect(_accessArea, actor->GetCollision())) {
				return true;
			}
		}
	}
	return false;
}

void MiniShuttle::CollisionUpdate() {
	if (_noCollision) {
		_collision.min = { -1,-1 };
		_collision.max = { -1,-1 };
	}
	else {
		_collision = _collisionPreset;
	}
}

void MiniShuttle::UpdateAnimation() {
	if (_game.GetFrameCount() % 2 == 0) {
		++_animNo;
	}

	if (!_cg2Flag) {
		if (_animNo >= _cg.size()) {
			_animNo = 0;
			_cg2Flag = true;
			_pos.y += 270;
			_noCollision = false;
		}
	}
	else {
		if (_animNo >= _cg2.size()) {
			_animNo = static_cast<int>(_cg2.size() - 1);
			if (_landing) {
				_controller.WarpEvent();
			}
		}
	}
}

void MiniShuttle::UpdateInverseAnimation() {
	if (_landing) {
		return;
	}
	if (_game.GetFrameCount() % 2 == 0) {
		--_animNo;
	}

	if (_cg2Flag) {
		if (_animNo < 0) {
			_noCollision = true;
			_animNo = static_cast<int>(_cg.size() - 1);
			_cg2Flag = false;
			_pos.y -= 270;
		}
	}
	else {
		if (_animNo < 0) {
			_animNo = 0;
			_dead = true;
			_controller.SpawnMiniShuttle();
		}
	}
}