/*****************************************************************//**
 * \file   LightBase.cpp
 * \brief  ���i�}�X�N�摜�j�̐e�N���X�ł��B
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/
#include "LightBase.h"
#include "Actor.h"
#include "ImageServer.h"

LightBase::LightBase(Game& game, ModeBase& mode, Actor& owner)
	:Actor{ game,mode }, _owner{ owner }, _angle{ 0 }, _scale{ 0.7 }
	, _centerPos{ _pos + _size / 2 },_alpha{255}
{
	int x, y;
	GetGraphSize(_cg, &x, &y);
	x *= _scale;
	y *= _scale;
	_pos = { _owner.GetPosition().x - x / 2 + 40,_owner.GetPosition().y - y / 2 + 40 };
	_cg = ImageServer::LoadGraph("resource/Light/Light_3.png");
}

void LightBase::Update() {
	if (_dead == false) {
		int x, y;
		GetGraphSize(_cg, &x, &y);
		x *= _scale;
		y *= _scale;
		_pos = { _owner.GetPosition().x - x / 2 + 40,_owner.GetPosition().y - y / 2 + 40 };
	}
}

void LightBase::CheckDeadOwner() {
	if (_owner.IsDead()){
		_dead = true;
	}
}
