#include "BossMissile.h"
#include "ModeGame.h"
#include "Explode.h"
#include "Bullet.h"

BossMissile::BossMissile(Game& game, ModeGame& mode, Vector2 pos) 
	:Actor(game,mode),_angle{Math::ToRadians(90)}, _player2{nullptr}, _speed{1.5}
{
	_room = { 0,0 };
	_pos = pos;
	_size = { 75,225 };

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
		_angle += Math::ToRadians(0.3f);
	}
	else if (dir_cross_a < 0) {
		_angle -= Math::ToRadians(0.3f);
	}
	_pos += GetForward()*_speed;
}

void BossMissile::HitActor() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB|| actor->GetType() == Type::Explode) {
			if(CheckOverlapActor(*actor)) {
				auto explode = std::make_unique<Explode2>(_game, _mode, _pos + (_size / 2));
				_mode.GetActorServer().Add(std::move(explode));
				_dead = true;
			}
		}
		if (actor->GetType() == Type::RedBullet|| actor->GetType() == Type::GreenBullet) {
			if (CheckOverlapActor(*actor)|| CheckCheckCrossBullet(*actor)) {
				auto explode = std::make_unique<Explode2>(_game, _mode, _pos + (_size / 2));
				_mode.GetActorServer().Add(std::move(explode));
				_dead = true;
				actor->Dead();
			}
		}
	}
}

bool BossMissile::CheckOverlapActor(Actor& actor) {
	auto col = actor.GetCollision();
	Vector2 righttop = { col.max.x,col.min.y };
	Vector2 leftbottom = { col.min.x,col.max.y };

	/*pos2,pos4とプレイヤーコリジョン4辺*/
	if (Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos2, col.min, righttop) ||
		Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos2, righttop, col.max) ||
		Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos2, col.max, leftbottom) ||
		Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos2, leftbottom, col.min)) {
		return 1;
	}
	/*pos2,pos4とプレイヤーコリジョン4辺*/
	if (Vector2::IsCrossed(_hitbox.pos2, _hitbox.pos4, col.min, righttop) ||
		Vector2::IsCrossed(_hitbox.pos2, _hitbox.pos4, righttop, col.max) ||
		Vector2::IsCrossed(_hitbox.pos2, _hitbox.pos4, col.max, leftbottom) ||
		Vector2::IsCrossed(_hitbox.pos2, _hitbox.pos4, leftbottom, col.min)) {
		return 1;
	}
	/*pos1,pos3とプレイヤーコリジョン4辺*/
	if (Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos3, col.min, righttop) ||
		Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos3, righttop, col.max) ||
		Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos3, col.max, leftbottom) ||
		Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos3, leftbottom, col.min)) {
		return 1;
	}
	/*pos3,pos4とプレイヤーコリジョン4辺*/
	if (Vector2::IsCrossed(_hitbox.pos3, _hitbox.pos4, col.min, righttop) ||
		Vector2::IsCrossed(_hitbox.pos3, _hitbox.pos4, righttop, col.max) ||
		Vector2::IsCrossed(_hitbox.pos3, _hitbox.pos4, col.max, leftbottom) ||
		Vector2::IsCrossed(_hitbox.pos3, _hitbox.pos4, leftbottom, col.min)) {
		return 1;
	}
	/*視界内に完全に納まっている場合の確認*/
	if (Vector2::Cross(_hitbox.pos1 - _hitbox.pos3, col.min - _hitbox.pos3) < 0 &&
		Vector2::Cross(_hitbox.pos3 - _hitbox.pos4, col.min - _hitbox.pos4) < 0 &&
		Vector2::Cross(_hitbox.pos4 - _hitbox.pos2, col.min - _hitbox.pos2) < 0 &&
		Vector2::Cross(_hitbox.pos2 - _hitbox.pos1, col.min - _hitbox.pos1) < 0) {
		return 1;
	}
return 0;
}

bool BossMissile::CheckCheckCrossBullet(Actor& actor) {
	Vector2 pre_pos=dynamic_cast<Bullet&>(actor).GetPrePosition();
	Vector2 pos = dynamic_cast<Bullet&>(actor).GetPosition();
	if (Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos2, pre_pos, pos) ||
		Vector2::IsCrossed(_hitbox.pos2, _hitbox.pos4, pre_pos, pos) ||
		Vector2::IsCrossed(_hitbox.pos1, _hitbox.pos3, pre_pos, pos) ||
		Vector2::IsCrossed(_hitbox.pos3, _hitbox.pos4, pre_pos, pos)) {
		return true;
	}
	return false;
}

void BossMissile::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
	DrawRotaGraph(static_cast<int>(_pos.x-camera_pos.x+window_pos.x),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
		1.0,_angle-Math::ToRadians(90),
		_cg,1,0);
}

void BossMissile::Debug(Vector2 window_pos, Vector2 camera_pos){
	DrawLine(static_cast<int>(_pos.x), static_cast<int>(_pos.y),
		static_cast<int>(_pos.x + GetForward().x * 100), static_cast<int>(_pos.y + GetForward().y * 100), GetColor(255, 0, 0), 1);
	//_collision.Draw2(stageNum, window_pos, camera_pos);

	/*視野範囲表示*/
	DrawLine(static_cast<int>(_hitbox.pos1.x + window_pos.x - camera_pos.x),
		static_cast<int>(_hitbox.pos1.y + window_pos.y - camera_pos.y),
		static_cast<int>(_hitbox.pos2.x + window_pos.x - camera_pos.x),
		static_cast<int>(_hitbox.pos2.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);
	DrawLine(static_cast<int>(_hitbox.pos1.x + window_pos.x - camera_pos.x),
		static_cast<int>(_hitbox.pos1.y + window_pos.y - camera_pos.y),
		static_cast<int>(_hitbox.pos3.x + window_pos.x - camera_pos.x),
		static_cast<int>(_hitbox.pos3.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);
	DrawLine(static_cast<int>(_hitbox.pos2.x + window_pos.x - camera_pos.x),
		static_cast<int>(_hitbox.pos2.y + window_pos.y - camera_pos.y),
		static_cast<int>(_hitbox.pos4.x + window_pos.x - camera_pos.x),
		static_cast<int>(_hitbox.pos4.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);
	DrawLine(static_cast<int>(_hitbox.pos3.x + window_pos.x - camera_pos.x),
		static_cast<int>(_hitbox.pos3.y + window_pos.y - camera_pos.y),
		static_cast<int>(_hitbox.pos4.x + window_pos.x - camera_pos.x),
		static_cast<int>(_hitbox.pos4.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);

}

void BossMissile::UpdateCollision(){
	//_collision.min = _pos-_size/2;
	//_collision.max = _pos + _size/2;
	auto angle = _angle+ Math::ToRadians(90);

	_hitbox.pos1 = { ( - 1 * _size.x / 2)* cos(angle) - (-1 * _size.y / 2) * sin(angle) + _pos.x,
	( - 1 * _size.x / 2) * sin(angle) + (-1 * _size.y / 2) * cos(angle) + _pos.y};
	
	_hitbox.pos2 = { _size.x / 2 * cos(angle) - ( - 1 * _size.y / 2) * sin(angle) + _pos.x,
	_size.x / 2 * sin(angle) + ( - 1 * _size.y / 2) * cos(angle) + _pos.y};

	_hitbox.pos3 = { ( - 1 * _size.x / 2)* cos(angle) - _size.y / 2 * sin(angle) + _pos.x,
	( - 1 * _size.x / 2) * sin(angle) + _size.y / 2 * cos(angle) + _pos.y};

	_hitbox.pos4 = { _size.x / 2 * cos(angle) - _size.y / 2 * sin(angle)+_pos.x,
	_size.x / 2 * sin(angle) + _size.y / 2 * cos(angle)+_pos.y };
}
