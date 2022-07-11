/*****************************************************************//**
 * \file   Actor.h
 * \brief  アクター（画面に表示される物体）の親クラスです。
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "Actor.h"

Actor::Actor(ModeBase& mode) : _mode{ mode }, _pos{ 0,0 }, _size{ 40,40 }, _dead{ false }, _stage{ -1 },_validLight{false}
{
	_collision.min = { _pos };
	_collision.max = { _pos + _size };
}

Actor::~Actor() {}

void Actor::Update() {

}

void Actor::StandardRender(int stageNum,Vector2 window_pos, Vector2 camera_pos) {
	
}

void Actor::ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {

}

void Actor::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) {

}

Actor::Type Actor::GetType() {
	return Actor::Type::Actor;
}


