#include "BossMissile.h"
#include "ModeGame.h"
#include "Explode.h"

BossMissile::BossMissile(Game& game, ModeGame& mode, Vector2 pos) 
	:Actor(game,mode),_angle{Math::ToRadians(90)}, _player2{nullptr}, _speed{1.5}
{
	_room = { 0,0 };
	_pos = pos;
	_size = { 30,90 };

	UpdateCollision();

	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType()==Type::PlayerB) {
			_player2=actor.get();
		}
	}

	_cg = ImageServer::LoadGraph("resource/Boss/missile.png");
}

void BossMissile::Update() {
	Move();

	UpdateCollision();
	HitActor();
	if (_room.x != CheckRoomPosition().x|| _room.y != CheckRoomPosition().y) {
		_dead = true;
	}
}

void BossMissile::Move() {
	auto p2_col=_player2->GetCollision();
	//auto a = (p2_col.min+p2_col.max) / 2-(_pos + _size)/2;
	auto a = p2_col.min -_pos;
	a.Normalize();
	/*ミサイルの移動方向と敵の位置までのベクトルの外積*/
	auto dir_cross_a = Vector2::Cross(GetForward(), a);

	if (dir_cross_a > 0) {
		_angle += Math::ToRadians(0.1f);
	}
	else if (dir_cross_a < 0) {
		_angle -= Math::ToRadians(0.1f);
	}
	_pos += GetForward()*_speed;
}

void BossMissile::HitActor() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB|| actor->GetType() == Type::Explode) {
			if(Intersect(_collision, actor->GetCollision())) {
				auto explode = std::make_unique<Explode>(_game, _mode, _pos + (_size / 2));
				_mode.GetActorServer().Add(std::move(explode));
				_dead = true;
			}
		}
		if (actor->GetType() == Type::RedBullet) {
			if (Intersect(_collision, actor->GetCollision())) {
				auto explode = std::make_unique<Explode>(_game, _mode, _pos + (_size / 2));
				_mode.GetActorServer().Add(std::move(explode));
				_dead = true;
				actor->Dead();
			}
		}
	}
}

void BossMissile::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawRotaGraph(static_cast<int>(_pos.x-camera_pos.x+window_pos.x+_size.x/2),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y+_size.y / 2),
		1.0,_angle-Math::ToRadians(90),
		_cg,1,0);
}

void BossMissile::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	DrawLine(_pos.x,_pos.y, _pos.x + GetForward().x*100, _pos.y + GetForward().y * 100,GetColor(255,0,0),1);
	_collision.Draw2(stageNum, window_pos, camera_pos);
}

void BossMissile::UpdateCollision(){
	_collision.min = _pos;
	_collision.max = _pos + _size;
}
