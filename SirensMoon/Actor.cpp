/*****************************************************************//**
 * \file   Actor.h
 * \brief  アクターの親クラスです。抽象クラス
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "Actor.h"
#include "Game.h"


Actor::Actor(Game& game, ModeGame& mode) 
	: _game{ game }, _mode{ mode }, _pos{ 0,0 }, _size{ 40,40 }, _dead{ false }, _stage{ -1 }, _cg{-1},_roomPosition{1,1}
{
	_collision.min =  _pos ;
	_collision.max =  _pos + _size ;
}

Actor::~Actor() {}

void Actor::Update() {

}

void Actor::StandardRender(int stageNum,Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 1);
}

void Actor::ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {

}

void Actor::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(stageNum, window_pos, camera_pos);
}

void Actor::CheckDeadOwner() {

}


void Actor::CheckRoomPosition() {
	double x = floor((_pos.x + _size.x / 2.0) / (static_cast<double>(splitscreen_W)));
	double y = floor((_pos.y + _size.y / 2.0) / (static_cast<double>(screen_H)));
	_roomPosition = { x,y };
	_renderPriority = _collision.max.y;
}