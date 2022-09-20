/*****************************************************************//**
 * \file   Bullet.h
 * \brief  ÉvÉåÉCÉÑÅ[Ç™î≠éÀÇ∑ÇÈèeíe
 *
 * \author amg
 * \date   July 2022
 *********************************************************************/
#include "Bullet.h"
#include "ModeGame.h"
#include "Gimmick.h"



Bullet::Bullet(Game& game, ModeGame& mode, Vector2 pos, double dir)
	:Actor{ game,mode }, _dir{ dir }, _speed{ 25 }, _lifetime{ 180 }
{
	_cg = ImageServer::LoadGraph("resource/Bullet/Bullet_1.png");
	_pos = pos;
	_prePos = pos;
	_size = { 30,30 };

	auto light = std::make_unique<LightBase>(_game,_mode,*this);
	_mode.GetActorServer().Add(std::move(light));
}

Bullet::~Bullet() {

}

void Bullet::Update() {
	_prePos = _pos;
	_pos.x += cos(_dir) * _speed;
	_pos.y += sin(_dir) * _speed;
	_renderPriority = static_cast<int>(_collision.max.y);
	UpdateCollision();

	--_lifetime;

	if (_lifetime < 0) {

		Dead();
	}
	if (dynamic_cast<ModeGame&>(_mode).GetMapChips()->IsHit(_collision,false)) {
		Dead();
		
	}
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::Gimmick) {
			if (dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::Door ||
				dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::Switch ||
				dynamic_cast<Gimmick&>(*actor).GetGimmickType() == Gimmick::GimmickType::TNT) {
				if (Intersect(actor->GetCollision(), _collision)) {
					Dead();
				}
			}
		}
	}
}

void Bullet::UpdateCollision() {
	_collision.min = _pos;
	_collision.max = _pos + _size;
}

void Bullet::StandardRender(Vector2 window_pos, Vector2 camera_pos){
	DrawRotaGraph(static_cast<int>(_pos.x-_size.x/2 + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y+_size.y/2 + window_pos.y - camera_pos.y)
		,1.0
		,_dir
		, _cg
		, 1);

}

void Bullet::Dead(){
	PlaySoundMem(SoundServer::Find("HitBullet"), DX_PLAYTYPE_BACK);
	_dead = true;
}
