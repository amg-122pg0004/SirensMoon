#pragma once
#include "BigServer.h"
#include "Game.h"
#include "ModeGame.h"
#include "BigServerUI.h"

BigServer::BigServer(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data, std::vector<int> pattern)
	:Gimmick(game,mode,data.ID),_pattern{pattern},_accessible{false}
{
	
	_pos = data.pos;
	Vector2 window_pos = _mode.GetSplitWindow()[1]->GetWindowPos();
	Vector2 ui_size{780,420};
	Vector2 ui_pos{window_pos.x+75,screen_H-420};
	auto UI = std::make_unique<BigServerUI>(_game,_mode,ui_pos,ui_size,*this);
	_mode.GetSplitWindow()[1]->GetUIServer().push_back(std::move(UI));
}

void BigServer::Update(){

}

void BigServer::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
		_cg, 0);
}