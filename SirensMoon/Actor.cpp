/*****************************************************************//**
 * \file   Actor.h
 * \brief  �A�N�^�[�i��ʂɕ\������镨�́j�̐e�N���X�ł��B
 *
 * \author �y�������Y
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



