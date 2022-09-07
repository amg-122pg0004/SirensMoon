#pragma once
#include "BigServer.h"
#include "Game.h"
#include "ModeGame.h"
#include "BigServerUI.h"

BigServer::BigServer(Game& game, ModeGame& mode, BigServerData data)
	:Gimmick(game,mode,data.ID),_accessible{false},_pattern{}
{
	_accessArea.min = { 0,0 };
	_accessArea.max = { 0,0 };
	_activate = false;

	_pos = data.pos;
	_collision.min = _pos;
	
	Vector2 window_pos = _mode.GetSplitWindow()[1]->GetWindowPos();
	Vector2 ui_size{780,420};
	Vector2 ui_pos{window_pos.x+75,screen_H-420};
	auto UI = std::make_unique<BigServerUI>(_game,_mode,ui_pos,ui_size,*this);
	_mode.GetSplitWindow()[1]->GetUIServer().push_back(std::move(UI));

	if (data.Direction == "up") {
		_cg.first = ImageServer::LoadGraph("resource/BossServer/up_p.png");
		_cg.second = ImageServer::LoadGraph("resource/BossServer/up.png");
		Vector2 size = { 87,44 };
		_collision.max = _pos + size;
		_accessArea.min = { _pos.x ,_pos.y - 10 };
		_accessArea.max = { _pos.x + size.x , _pos.y + size.y };
	}
	else 	if (data.Direction == "right") {
		_cg.first = ImageServer::LoadGraph("resource/BossServer/right_p.png");
		_cg.second = ImageServer::LoadGraph("resource/BossServer/right.png");
		Vector2 size = { 44,87 };
		_collision.max = _pos + size;
		_accessArea.min = { _pos.x + size.x,_pos.y };
		_accessArea.max = { _pos.x + size.x + 10,_pos.y + size.y };
	}
	else if (data.Direction == "down") {
		_cg.first = ImageServer::LoadGraph("resource/BossServer/down_p.png");
		_cg.second = ImageServer::LoadGraph("resource/BossServer/down.png");
		Vector2 size = { 87,44 };
		_collision.max = _pos + size;
		_accessArea.min = { _pos.x,_pos.y + size.y };
		_accessArea.max = { _pos.x + size.x,_pos.y + size.y + 10 };
	}
	else if (data.Direction == "left") {
		_cg.first = ImageServer::LoadGraph("resource/BossServer/left_p.png");
		_cg.second = ImageServer::LoadGraph("resource/BossServer/left.png");
		Vector2 size = { 44,87 };
		_collision.max = _pos + size;
		_accessArea.min = { _pos.x - 10,_pos.y };
		_accessArea.max = { _pos.x,_pos.y + size.y };
	}
}

void BigServer::Update(){
	if (_activate) {
		for (auto&& actor : _mode.GetObjects()) {
			if (actor->GetType() == Type::PlayerB) {
				if (Intersect(_accessArea, actor->GetCollision())) {
					_accessible = true;
				}
				else {
					_accessible = false;
				}
			}
		}
	}
}

void BigServer::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(window_pos, camera_pos);
	_accessArea.Draw2(window_pos, camera_pos);
}

void BigServer::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	int cg{ -1 };
	if (_pattern.size() == 0) {
		cg = _cg.first;
	}
	else {
		cg = _cg.second;
	}
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
		cg, 1);
}

void BigServer::SetPattern(std::vector<int> pattern) {
	_pattern = pattern;
}