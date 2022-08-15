/*****************************************************************//**
 * \file   Enemy.cpp
 * \brief  基本敵キャラクター
 *
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "Enemy.h"
#include "Game.h"
#include "ModeGame.h"
#include "BlinkLight.h"
#include <random>
#include "MapChip.h"

Enemy::Enemy(Game& game, ModeGame& mode, EnemyGenerator::EnemyPattern pattern)
	:Actor{ game,mode }, _speed{ 1 }, _sight_H{ 210 }, _sight_W{ 330 }, _detectionFrame{ 0 }, _chase{ false }, _pattern{ pattern }
{
	_size = { 200,200 };

	SetGrHandle(pattern);
	Init();
};

void Enemy::Init() {
	for (auto&& actor : _mode.GetObjects()) {
		if (actor->GetType() == Actor::Type::PlayerA) {
			_lastDetection = actor.get();
		}
	}
}

void Enemy::Update() {
	CheckDamage();
	_eyelineGrids.clear();
	SightUpdate();
	CheckRoomPosition();
	if (CheckDetection()) {
		if (CheckVisualLine()) {
			++_detectionFrame;
			if (_detectionFrame >= 120) {
				_speed = 12;
				_chase = true;
			}
		}
		else {
			_detectionFrame = 0;
		}
	}
	else {
		_detectionFrame = 0;
	}
	AnimationUpdate();
	UpdateCollision();

}

void Enemy::AnimationUpdate() {
	_animeNo = _game.GetFrameCount() / 2 % 29;
	SetDirection();
}

void Enemy::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawExtendGraph(static_cast<int>(_pos.x - (_size.x / 2) + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y - (_size.y / 2) + window_pos.y - camera_pos.y),
		static_cast<int>(_pos.x - (_size.x / 2) + window_pos.x - camera_pos.x + _size.x),
		static_cast<int>(_pos.y - (_size.y / 2) + window_pos.y - camera_pos.y + _size.y),
		_cg_bot[_cg_direction],
		1);
	DrawExtendGraph(static_cast<int>(_pos.x - (_size.x / 2) + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y - (_size.y / 2) + window_pos.y - camera_pos.y),
		static_cast<int>(_pos.x - (_size.x / 2) + window_pos.x - camera_pos.x + _size.x),
		static_cast<int>(_pos.y - (_size.y / 2) + window_pos.y - camera_pos.y + _size.y),
		_cg_top2[_cg_direction],
		1);
	DrawExtendGraph(static_cast<int>(_pos.x - (_size.x / 2) + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y - (_size.y / 2) + window_pos.y - camera_pos.y),
		static_cast<int>(_pos.x - (_size.x / 2) + window_pos.x - camera_pos.x + _size.x),
		static_cast<int>(_pos.y - (_size.y / 2) + window_pos.y - camera_pos.y + _size.y),
		_cg_mid[_cg_direction],
		1);
	DrawExtendGraph(static_cast<int>(_pos.x - (_size.x / 2) + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y - (_size.y / 2) + window_pos.y - camera_pos.y),
		static_cast<int>(_pos.x - (_size.x / 2) + window_pos.x - camera_pos.x + _size.x),
		static_cast<int>(_pos.y - (_size.y / 2) + window_pos.y - camera_pos.y + _size.y),
		_cg_top[_cg_direction],
		1);
}

void Enemy::SightUpdate() {
	_eyePos = _pos;// +_size / 2;
	auto fov = _eyePos + _dir * _sight_W;
	Vector2 dirside = { _dir.y * -1,_dir.x };//<視界に垂直なベクトル
	/*視界範囲4点作成*/
	_sightPos.pos1 = { _eyePos.x - dirside.x * (_sight_H / 2),_eyePos.y - dirside.y * (_sight_H / 2) };
	_sightPos.pos2 = { _eyePos.x + dirside.x * (_sight_H / 2),_eyePos.y + dirside.y * (_sight_H / 2) };
	_sightPos.pos3 = { (_eyePos + _dir * _sight_W).x - dirside.x * (_sight_H / 2),(_eyePos + _dir * _sight_W).y - dirside.y * (_sight_H / 2) };
	_sightPos.pos4 = { (_eyePos + _dir * _sight_W).x + dirside.x * (_sight_H / 2),(_eyePos + _dir * _sight_W).y + dirside.y * (_sight_H / 2) };
}

bool Enemy::CheckDetection() {
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
			CheckRoomPosition();
			if (_roomPosition.x == actor->GetRoomPosition().x && _roomPosition.y == actor->GetRoomPosition().y) {
				//if(1){
				auto col = actor->GetCollision();
				Vector2 righttop = { col.max.x,col.min.y };
				Vector2 leftbottom = { col.min.x,col.max.y };

				AABB enemyaround = { {0,0},{0,0} };
				enemyaround.min = { _eyePos.x - 60,_eyePos.y - 75 };
				enemyaround.max = { _eyePos.x + 60,_eyePos.y + 75 };
				/*周辺判定*/
				if (Intersect(enemyaround, col)) {
					_lastDetection = actor.get();
					return 1;
				}
				/*pos1,pos2は周辺判定の範囲に含まれるため判定を行わない*/
				/*pos2,pos4とプレイヤーコリジョン4辺*/
				if (Vector2::IsCrossed(_sightPos.pos2, _sightPos.pos4, col.min, righttop) ||
					Vector2::IsCrossed(_sightPos.pos2, _sightPos.pos4, righttop, col.max) ||
					Vector2::IsCrossed(_sightPos.pos2, _sightPos.pos4, col.max, leftbottom) ||
					Vector2::IsCrossed(_sightPos.pos2, _sightPos.pos4, leftbottom, col.min)) {
					_lastDetection = actor.get();
					return 1;
				}
				/*pos1,pos3とプレイヤーコリジョン4辺*/
				if (Vector2::IsCrossed(_sightPos.pos1, _sightPos.pos3, col.min, righttop) ||
					Vector2::IsCrossed(_sightPos.pos1, _sightPos.pos3, righttop, col.max) ||
					Vector2::IsCrossed(_sightPos.pos1, _sightPos.pos3, col.max, leftbottom) ||
					Vector2::IsCrossed(_sightPos.pos1, _sightPos.pos3, leftbottom, col.min)) {
					_lastDetection = actor.get();
					return 1;
				}
				/*pos3,pos4とプレイヤーコリジョン4辺*/
				if (Vector2::IsCrossed(_sightPos.pos3, _sightPos.pos4, col.min, righttop) ||
					Vector2::IsCrossed(_sightPos.pos3, _sightPos.pos4, righttop, col.max) ||
					Vector2::IsCrossed(_sightPos.pos3, _sightPos.pos4, col.max, leftbottom) ||
					Vector2::IsCrossed(_sightPos.pos3, _sightPos.pos4, leftbottom, col.min)) {
					_lastDetection = actor.get();
					return 1;
				}
				/*視界内に完全に納まっている場合の確認*/
				if (Vector2::Cross(_sightPos.pos1 - _sightPos.pos3, col.min - _sightPos.pos3) < 0 &&
					Vector2::Cross(_sightPos.pos3 - _sightPos.pos4, col.min - _sightPos.pos4) < 0 &&
					Vector2::Cross(_sightPos.pos4 - _sightPos.pos2, col.min - _sightPos.pos2) < 0 &&
					Vector2::Cross(_sightPos.pos2 - _sightPos.pos1, col.min - _sightPos.pos1) < 0) {
					_lastDetection = actor.get();
					return 1;
				}
			}
		}
	}
	return 0;
}


bool Enemy::CheckVisualLine() {

	Vector2 target_pos = _lastDetection->GetPosition();

	for (double pix_x = _eyePos.x; pix_x <= target_pos.x; pix_x = pix_x + (target_pos.x - _eyePos.x) / 50) {
		int pix_y = (target_pos.y - _eyePos.y) / (target_pos.x - _eyePos.x) * (pix_x - _eyePos.x) + _eyePos.y;
		_eyelineGrids.insert({ pix_x / 30, pix_y / 30 });
	}
	for (double pix_x = _eyePos.x; pix_x > target_pos.x; pix_x = pix_x + (target_pos.x - _eyePos.x) / 50) {
		int pix_y = (target_pos.y - _eyePos.y) / (target_pos.x - _eyePos.x) * (pix_x - _eyePos.x) + _eyePos.y;
		_eyelineGrids.insert({ pix_x / 30, pix_y / 30 });
	}

	if (_mode.GetMapChips()->IsHit(_eyelineGrids)) {
		return false;
	}
	else {
		return true;
	}
}

void Enemy::SetDirection() {
	double dir_rad = atan2(_dir.y, _dir.x);
	double pi = 3.141519;
	double dir_deg = (dir_rad) * 180 / 3.14;

	if (-180 < dir_deg && dir_deg <= -140) {
		_cg_direction = EnemyDirection::Left;
	}
	else if (-140 < dir_deg && dir_deg <= -100) {
		_cg_direction = EnemyDirection::UpLeft;
	}
	else if (-100 < dir_deg && dir_deg <= -60) {
		_cg_direction = EnemyDirection::Up;
	}
	else if (-60 < dir_deg && dir_deg <= -20) {
		_cg_direction = EnemyDirection::UpRight;
	}
	else if (-20 < dir_deg && dir_deg <= 20) {
		_cg_direction = EnemyDirection::Right;
	}
	else if (20 < dir_deg && dir_deg <= 60) {
		_cg_direction = EnemyDirection::DownRight;
	}
	else if (60 < dir_deg && dir_deg <= 100) {
		_cg_direction = EnemyDirection::Down;
	}
	else if (100 < dir_deg && dir_deg <= 140) {
		_cg_direction = EnemyDirection::DownLeft;
	}
	else if (140 < dir_deg && dir_deg <= 180) {
		_cg_direction = EnemyDirection::Left;
	}
}

void Enemy::CheckDamage() {
	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
		if (actor->GetType() == Type::RedBullet) {
			if (Intersect(_collision, actor->GetCollision())) {
				actor->Dead();
				_dead = true;
				PlaySoundMem(SoundServer::Find("BulletToEnemy"), DX_PLAYTYPE_BACK);
			}
		}
		if (actor->GetType() == Type::GreenBullet) {
			if (Intersect(_collision, actor->GetCollision())) {
				_speed = 15;
				_chase = true;
				PlaySoundMem(SoundServer::Find("BulletToEnemy"), DX_PLAYTYPE_BACK);
			}
		}
		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
			if (Intersect(_collision, actor->GetCollision())) {
				ApplyDamage();
			}
		}
	}
}

void Enemy::MoveToPlayer() {
	auto col = dynamic_cast<Player&>(*_lastDetection).GetCollision();
	_dir = (col.min + col.max) / 2 - (_collision.min + _collision.max) / 2;
	_dir.Normalize();
	_pos += _dir * _speed;
}

void Enemy::ApplyDamage() {
	PlaySoundMem(SoundServer::Find("DamageToPlayer"), DX_PLAYTYPE_BACK);
	dynamic_cast<Player&>(*_lastDetection).TakeDamage();
	_dead = true;
}

void Enemy::UpdateCollision() {
	_collision.min = { _pos.x - _size.x / 2 + 70 , _pos.y - _size.y / 2 + 30 };
	_collision.max = { _pos.x + _size.x / 2 - 70,_pos.y + _size.y / 2 - 30 };
}

void Enemy::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(stageNum, window_pos, camera_pos);
	DrawBox((_collision.min.x + _collision.max.x) / 2.0 + window_pos.x - camera_pos.x,
		(_collision.min.y + _collision.max.y) / 2.0 + window_pos.y - camera_pos.y,
		(_collision.min.x + _collision.max.x) / 2.0 + window_pos.x - camera_pos.x + 1,
		(_collision.min.y + _collision.max.y) / 2.0 + window_pos.y - camera_pos.y + 1,
		GetColor(255, 255, 0), 1);
	/*周辺知覚範囲表示*/
	DrawBox(static_cast<int>(_eyePos.x + window_pos.x - camera_pos.x - 60),
		static_cast<int>(_eyePos.y + window_pos.y - camera_pos.y - 75),
		static_cast<int>(_eyePos.x + window_pos.x - camera_pos.x + 60),
		static_cast<int>(_eyePos.y + window_pos.y - camera_pos.y + 75),
		GetColor(255, 0, 0), 0);

	/*視野範囲表示*/
	DrawLine(static_cast<int>(_sightPos.pos1.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos1.y + window_pos.y - camera_pos.y),
		static_cast<int>(_sightPos.pos2.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos2.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);
	DrawLine(static_cast<int>(_sightPos.pos2.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos2.y + window_pos.y - camera_pos.y),
		static_cast<int>(_sightPos.pos4.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos4.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);
	DrawLine(static_cast<int>(_sightPos.pos4.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos4.y + window_pos.y - camera_pos.y),
		static_cast<int>(_sightPos.pos3.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos3.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);
	DrawLine(static_cast<int>(_sightPos.pos3.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos3.y + window_pos.y - camera_pos.y),
		static_cast<int>(_sightPos.pos1.x + window_pos.x - camera_pos.x),
		static_cast<int>(_sightPos.pos1.y + window_pos.y - camera_pos.y),
		GetColor(255, 0, 0), 1);


	if (_roomPosition.x == _lastDetection->GetRoomPosition().x && _roomPosition.y == _lastDetection->GetRoomPosition().y) {
		Vector2 target_pos = _lastDetection->GetPosition();
		DrawLine(static_cast<int>(_eyePos.x) + window_pos.x - camera_pos.x,
			static_cast<int>(_eyePos.y) + window_pos.y - camera_pos.y,
			static_cast<int>(target_pos.x) + window_pos.x - camera_pos.x,
			static_cast<int>(target_pos.y) + window_pos.y - camera_pos.y,
			GetColor(255, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
		for (auto&& grid : _eyelineGrids) {
			DrawBox(grid.first * 30 + window_pos.x - camera_pos.x,
				grid.second * 30 + window_pos.y - camera_pos.y,
				grid.first * 30 + 30 + window_pos.x - camera_pos.x,
				grid.second * 30 + 30 + window_pos.y - camera_pos.y,
				GetColor(255, 0, 0), 1);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	//発見フレーム数表示
	std::stringstream ss;
	ss << "発見フレーム数" << _detectionFrame << "\n";
	ss << "room" << _roomPosition.x << "," << _roomPosition.y << "\n";
	DrawString(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
		static_cast<int>(_pos.y + window_pos.y - camera_pos.y - 10),
		ss.str().c_str(), GetColor(255, 0, 255));
}

void Enemy::SetGrHandle(EnemyGenerator::EnemyPattern pattern) {

	/*
Resize(_cg_top);
Resize(_cg_top2);
Resize(_cg_mid);
Resize(_cg_bot);
*/

	switch (pattern.head) {
	case 1:
		_cg_top[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_down.png");
		_cg_top[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_downleft.png");
		_cg_top[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_left.png");
		_cg_top[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_upleft.png");
		_cg_top[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_up.png");
		_cg_top[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_upright.png");
		_cg_top[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_right.png");
		_cg_top[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head1(1)/head1_downright.png");

		_cg_top2[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		break;
	case 2:
		_cg_top[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_down.png");
		_cg_top[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_downleft.png");
		_cg_top[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_left.png");
		_cg_top[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_upleft.png");
		_cg_top[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_up.png");
		_cg_top[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_upright.png");
		_cg_top[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_right.png");
		_cg_top[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_downright.png");

		_cg_top2[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_downleft.png");
		_cg_top2[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_left.png");
		_cg_top2[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_upleft.png");
		_cg_top2[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_upright.png");
		_cg_top2[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_right.png");
		_cg_top2[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_downright.png");
		break;
	case 3:
		_cg_top[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_down.png");
		_cg_top[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_downleft.png");
		_cg_top[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_left.png");
		_cg_top[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_upleft.png");
		_cg_top[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_up.png");
		_cg_top[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_upright.png");
		_cg_top[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_right.png");
		_cg_top[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head2(1)/head2_downright.png");

		_cg_top2[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_downleft.png");
		_cg_top2[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_left.png");
		_cg_top2[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_upleft.png");
		_cg_top2[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_upright.png");
		_cg_top2[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_right.png");
		_cg_top2[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/head2(2)/head2_downright.png");
		break;
	}
	switch (pattern.body) {
	case 1:
		_cg_mid[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/body1/body1_down.png");
		_cg_mid[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/body1/body1_downleft.png");
		_cg_mid[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/body1/body1_left.png");
		_cg_mid[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/body1/body1_upleft.png");
		_cg_mid[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/body1/body1_up.png");
		_cg_mid[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/body1/body1_upright.png");
		_cg_mid[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/body1/body1_right.png");
		_cg_mid[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/body1/body1_downright.png");
		break;
	case 2:
		_cg_mid[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/body2/body2_down.png");
		_cg_mid[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/body2/body2_downleft.png");
		_cg_mid[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/body2/body2_left.png");
		_cg_mid[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/body2/body2_upleft.png");
		_cg_mid[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/body2/body2_up.png");
		_cg_mid[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/body2/body2_upright.png");
		_cg_mid[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/body2/body2_right.png");
		_cg_mid[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/body2/body2_downright.png");
		break;
	case 3:
		_cg_mid[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/body2/body2_down.png");
		_cg_mid[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/body2/body2_downleft.png");
		_cg_mid[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/body2/body2_left.png");
		_cg_mid[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/body2/body2_upleft.png");
		_cg_mid[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/body2/body2_up.png");
		_cg_mid[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/body2/body2_upright.png");
		_cg_mid[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/body2/body2_right.png");
		_cg_mid[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/body2/body2_downright.png");
		break;
	}
	switch (pattern.foot) {
	case 1:
		_cg_bot[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_down.png");
		_cg_bot[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_downleft.png");
		_cg_bot[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_left.png");
		_cg_bot[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_upleft.png");
		_cg_bot[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_up.png");
		_cg_bot[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_upright.png");
		_cg_bot[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_right.png");
		_cg_bot[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/foot1/foot1_downright.png");
		break;
	case 2:
		_cg_bot[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_down.png");
		_cg_bot[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_downleft.png");
		_cg_bot[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_left.png");
		_cg_bot[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_upleft.png");
		_cg_bot[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_up.png");
		_cg_bot[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_upright.png");
		_cg_bot[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_right.png");
		_cg_bot[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_downright.png");
		break;
	case 3:
		_cg_bot[EnemyDirection::Down] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_down.png");
		_cg_bot[EnemyDirection::DownLeft] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_downleft.png");
		_cg_bot[EnemyDirection::Left] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_left.png");
		_cg_bot[EnemyDirection::UpLeft] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_upleft.png");
		_cg_bot[EnemyDirection::Up] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_up.png");
		_cg_bot[EnemyDirection::UpRight] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_upright.png");
		_cg_bot[EnemyDirection::Right] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_right.png");
		_cg_bot[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/foot2/foot2_downright.png");
		break;
	}
}

void Enemy::CheckRoomPosition() {
	double x = floor((_collision.min.x + _collision.max.x) / 2.0 / (static_cast<double>(splitscreen_W)));
	double y = floor((_collision.min.y + _collision.max.y) / 2.0 / (static_cast<double>(screen_H)));
	_roomPosition = { x,y };
}
