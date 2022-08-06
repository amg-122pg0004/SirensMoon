#include "FloorLamp.h"
#include <memory>
#include "ModeGame.h"

FloorLamp::FloorLamp(Game& game, ModeGame& mode, int ID, SquareLight::SquareLightStats stats)
	:Gimmick(game,mode, ID)
{
	_activate = stats.activate;
	_pos = stats.pos;
	_size = stats.size;

	auto light = std::make_unique<SquareLight>(game, mode,*this,stats );
	mode.GetActorServer().Add(std::move(light));
}

void FloorLamp::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	DrawBox(_pos.x+_size.x/2 - 5+window_pos.x-camera_pos.x,
		_pos.y+_size.y/2 - 5 +window_pos.y-camera_pos.y,
		_pos.x+_size.x/2 + 5 + window_pos.x - camera_pos.x,
		_pos.y+_size.y/2 + 5 + window_pos.y - camera_pos.y,
		GetColor(255, 255, 0), 1);
}
