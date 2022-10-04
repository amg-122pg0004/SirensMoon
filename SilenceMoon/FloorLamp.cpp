/*****************************************************************//**
 * \file   FloorLamp.cpp
 * \brief  設置用ライトオブジェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "FloorLamp.h"
#include <memory>
#include "ModeGame.h"

FloorLamp::FloorLamp(Game& game, ModeGame& mode,SquareLightStats stats)
	:Gimmick(game,mode, stats.ID)
{
	_cg = -1;
	if (stats.object != "NULL") {
		_cg = ImageServer::LoadGraph(stats.object);
	}
	//_cg = ImageServer::LoadGraph("resource/Gimmick/lamp.png");

	_activate = stats.activate;
	_pos = stats.pos;
	_size = stats.size;

	auto light = std::make_unique<SquareLight>(game, mode,*this,stats );
	mode.GetActorServer().Add(std::move(light));
}

void FloorLamp::Debug(Vector2 window_pos, Vector2 camera_pos){
	DrawBox(static_cast<int>(_pos.x + _size.x / 2 - 5 + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y+_size.y/2 - 5 +window_pos.y-camera_pos.y),
		static_cast<int>(_pos.x+_size.x/2 + 5 + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y+_size.y/2 + 5 + window_pos.y - camera_pos.y),
		GetColor(255, 255, 0), 1);
}

void FloorLamp::StandardRender(Vector2 window_pos, Vector2 camera_pos){
	DrawGraph(static_cast<int>(_pos.x + _size.x / 2  + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + _size.y / 2  + window_pos.y - camera_pos.y)
		, _cg
		, 1);
}
