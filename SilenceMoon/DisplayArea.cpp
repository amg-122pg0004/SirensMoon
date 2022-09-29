/*****************************************************************//**
 * \file   DisplayArea.cpp
 * \brief  ミニマップに攻撃範囲を表示するためのオブジェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "DisplayArea.h"

DisplayArea::DisplayArea(Game& game, ModeGame& mode, Actor& owner,bool left)
	:Actor(game, mode), _owner{ owner }, _lifetime{180}
{
	_pos = _owner.GetPosition();
	_size = { 500,3000 };
	_displayArea.min = _pos;
	if (left) {
		_displayArea.max = { _pos.x - _size.x , _pos.y + _size.y };
	}
	else {
		_displayArea.max = _pos + _size;
	}

}

void DisplayArea::Update() {
	--_lifetime;
	if (_lifetime < 0) {
		_dead = true;
	}
}
