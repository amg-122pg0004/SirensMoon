/*****************************************************************//**
 * \file   Bullet.h
 * \brief  ÉvÉåÉCÉÑÅ[Ç™î≠éÀÇ∑ÇÈèeíe
 *
 * \author amg
 * \date   July 2022
 *********************************************************************/
#include "Bullet.h"
#include "ImageServer.h"
#include "ModeGame.h"

Bullet::Bullet(Game& game, ModeBase& mode, Vector2 pos, Vector2 dir)
	:Actor{ game,mode }, _dir{ dir }, _speed{ 25 }, _lifetime{ 180 }
{
	_cg = ImageServer::LoadGraph("resource/Bullet/Bullet_1.png");
	_pos = pos;
	_size = { 5,5 };

	auto light = std::make_unique<LightBase>();
	_mode.GetActorServer().Add(std::move(light));
}

Bullet::~Bullet() {

}

void Bullet::Update() {
	_pos = _pos + _dir * _speed;
	--_lifetime;

	if (_lifetime < 0) {

		_dead = true;
	}
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHit(1, *this)) {
		_lightref->Dead();
		_dead = true;
	}
}

void Bullet::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 1);
}
