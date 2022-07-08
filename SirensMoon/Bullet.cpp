/*****************************************************************//**
 * \file   Bullet.h
 * \brief  ÉvÉåÉCÉÑÅ[Ç™î≠éÀÇ∑ÇÈèeíe
 *
 * \author amg
 * \date   July 2022
 *********************************************************************/
#include "Bullet.h"
#include "ImageServer.h"

Bullet::Bullet(Game& game,Vector2 pos, Vector2 dir) 
	:Actor{ game }, _dir{ dir }, _speed{ 25 }
{
	_cg = ImageServer::LoadGraph("resource/Bullet/Bullet_1.png");
	_pos = pos;

	auto light = std::make_unique<Light2>(_game,*this);
	_game.GetActorServer()->Add(std::move(light));

}

Bullet::~Bullet() {

}

void Bullet::Update() {
	_pos = _pos + _dir * _speed;
	
}

void Bullet::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 1);
}
