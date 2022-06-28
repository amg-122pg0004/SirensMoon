/*****************************************************************//**
 * \file   Actor.h
 * \brief  アクター（画面に表示される物体）の親クラスです。
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "Actor.h"

Actor::Actor(Game& game) : _game{ game }, _pos{ 0,0 }, _dead{false} {
}

Actor::~Actor() {}

void Actor::Update() {

}

void Actor::Render(Vector2 window_pos, Vector2 camera_pos) {
	
}



