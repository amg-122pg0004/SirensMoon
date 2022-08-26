#pragma once
#include "BigServer.h"
#include "Game.h"
#include "ModeGame.h"
#include "BigServerUI.h"

BigServer::BigServer(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data)
	:Gimmick(game,mode,data.ID),_accessible{false}
{
	_accessArea.min = { 0,0 };
	_accessArea.max = { 0,0 };
	_cg = ImageServer::LoadGraph("resoure/UI/wanted.png");
	_pos = data.pos;
	Vector2 window_pos = _mode.GetSplitWindow()[1]->GetWindowPos();
	Vector2 ui_size{780,420};
	Vector2 ui_pos{window_pos.x+75,screen_H-420};
	auto UI = std::make_unique<BigServerUI>(_game,_mode,ui_pos,ui_size,*this);
	_mode.GetSplitWindow()[1]->GetUIServer().push_back(std::move(UI));

	if (data.Direction == "up") {
		_accessArea.min = { _pos.x ,_pos.y - 10 };
		_accessArea.max = { _pos.x + _size.x , _pos.y + _size.y };
	}
	else 	if (data.Direction == "right") {
		_accessArea.min = { _pos.x + _size.x,_pos.y };
		_accessArea.max = { _pos.x + _size.x + 10,_pos.y + _size.y };
	}
	else if (data.Direction == "down") {
		_accessArea.min = { _pos.x,_pos.y + _size.y };
		_accessArea.max = { _pos.x + _size.x,_pos.y + _size.y + 10 };
	}
	else if (data.Direction == "left") {
		_accessArea.min = { _pos.x - 10,_pos.y };
		_accessArea.max = { _pos.x,_pos.y + _size.y };
	}
}

void BigServer::Update(){
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerB) {
			if(Intersect(_accessArea, actor->GetCollision())) {
				_accessible = true;
			}
			else {
				_accessible = false;
			}
		}
	}
}

void BigServer::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
		_cg, 0);


}

void BigServer::SetPattern(std::vector<int> pattern) {
	_pattern = pattern;
}
