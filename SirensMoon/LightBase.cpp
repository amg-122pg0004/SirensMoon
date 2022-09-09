/*****************************************************************//**
 * \file   LightBase.cpp
 * \brief  光（マスク画像）の親クラスです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/
#include "LightBase.h"
#include "Actor.h"
#include "ModeGame.h"

LightBase::LightBase(Game& game, ModeGame& mode, Actor& owner)
	:Actor{ game,mode }, _owner{ owner }, _angle{ 0 }, _scale{ 0.7 }
	, _centerPos{ _pos + _size / 2 },_alpha{255},_activate{true}
{
	int x, y;
	GetGraphSize(_cg, &x, &y);
	auto d_x =static_cast<double>( x * _scale);
	auto d_y =static_cast<double>( y * _scale);
	_pos = { _owner.GetPosition().x+_owner.GetSize().x - d_x / 2,_owner.GetPosition().y + _owner.GetSize().y - d_y / 2};
	_cg = ImageServer::LoadGraph("resource/Light/Light_3.png");
	_renderPriority = 100000;
}

void LightBase::Update() {
	if (_dead == false) {
		int x, y;
		GetGraphSize(_cg, &x, &y);
		double d_x = static_cast<double>(x) * _scale;
		double d_y = static_cast<double>(y) * _scale;
		_pos = { _owner.GetPosition().x + _owner.GetSize().x - d_x / 2 ,_owner.GetPosition().y + _owner.GetSize().y - d_y / 2 };
	}
}

void LightBase::CheckDeadOwner() {
	if (_owner.IsDead()){
		_dead = true;
	}
}

void LightBase::MaskRender(Vector2 window_pos, Vector2 camera_pos){
	if (_activate) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawRotaGraph2(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
			static_cast<int>(_centerPos.x),
			static_cast<int>(_centerPos.y),
			_scale,
			_angle,
			_cg, 1, 0);
	}
}
