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
	:Actor{ game,mode }, _speed{ 1 }, _sight_H{ 210 }, _sight_W{ 330 }
	,_detectionFrame{ 120 }, _chase{ false }, _pattern{ pattern }
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
	_roomPosition =CheckRoomPosition();
	if (CheckDetection()) {
		if (CheckVisualLine()) {
			++_detectionFrame;
			if (_detectionFrame == 1) {
				PlaySoundMem(SoundServer::Find("Detection"), DX_PLAYTYPE_BACK);
			}
			if (_detectionFrame >= _detectionCompleteFrame){
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
	_renderPriority = static_cast<int>(_collision.max.y);
}

void Enemy::AnimationUpdate() {
	_animeNo = _game.GetFrameCount() / 2 % 29;
	SetDirection();
}

void Enemy::StandardRender(Vector2 window_pos, Vector2 camera_pos) {
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
			if (dynamic_cast<Player&>(*actor).GetHideFlag()) {
				continue;
			}
			if (_roomPosition.x == actor->GetRoomPosition().x && _roomPosition.y == actor->GetRoomPosition().y) {
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
		int pix_y = static_cast<int>((target_pos.y - _eyePos.y) / (target_pos.x - _eyePos.x) * (pix_x - _eyePos.x) + _eyePos.y);
		_eyelineGrids.insert({ pix_x / 30, pix_y / 30 });
	}
	for (double pix_x = _eyePos.x; pix_x > target_pos.x; pix_x = pix_x + (target_pos.x - _eyePos.x) / 50) {
		int pix_y = static_cast<int>((target_pos.y - _eyePos.y) / (target_pos.x - _eyePos.x) * (pix_x - _eyePos.x) + _eyePos.y);
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
	double dir_deg = Math::ToDegrees(static_cast<float>(dir_rad));

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
		if (actor->GetType() == Type::RedBullet|| actor->GetType() == Type::Explode) {
			if (Intersect(_hitBox, actor->GetCollision())) {
				actor->Dead();
				TakeDamage(actor->GetType());
			}
		}
		if (actor->GetType() == Type::GreenBullet) {
			if (Intersect(_hitBox, actor->GetCollision())) {
				_speed = 15;
				_chase = true;
			}
		}
		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
			if (Intersect(_collision, actor->GetCollision())) {
				ApplyDamage();
			}
		}
	}
}

void Enemy::TakeDamage(Type) {
	_dead = true;
}

void Enemy::MoveToPlayer() {
	if (_roomPosition.x == _lastDetection->GetRoomPosition().x && _roomPosition.y == _lastDetection->GetRoomPosition().y) {
		auto col = dynamic_cast<Player&>(*_lastDetection).GetCollision();
		_dir = (col.min + col.max) / 2 - (_collision.min + _collision.max) / 2;
		_dir.Normalize();
		_pos += _dir * _speed;
	}
	else {
		_chase = false;
		_speed = 1;
	}
}

void Enemy::ApplyDamage() {
	dynamic_cast<Player&>(*_lastDetection).TakeDamage(GetType());
	TakeDamage(Type::Player);
}

void Enemy::UpdateCollision() {
	_collision.min = { _pos.x - _size.x / 2 + 90 , _pos.y - _size.y / 2 + 70 };
	_collision.max = { _pos.x + _size.x / 2 - 90,_pos.y + _size.y / 2-90 };
	_hitBox.min = { _pos.x - _size.x / 2 + 80 , _pos.y - _size.y / 2 + 40 };
	_hitBox.max = { _pos.x + _size.x / 2 - 80,_pos.y + _size.y / 2 - 75 };
}

void Enemy::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(window_pos, camera_pos);
	_hitBox.Draw2(window_pos, camera_pos);
	DrawBox(static_cast<int>((_collision.min.x + _collision.max.x) / 2.0 + window_pos.x - camera_pos.x),
		static_cast<int>((_collision.min.y + _collision.max.y) / 2.0 + window_pos.y - camera_pos.y),
		static_cast<int>((_collision.min.x + _collision.max.x) / 2.0 + window_pos.x - camera_pos.x + 1),
		static_cast<int>((_collision.min.y + _collision.max.y) / 2.0 + window_pos.y - camera_pos.y + 1),
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
		DrawLine(static_cast<int>(_eyePos.x + window_pos.x - camera_pos.x),
			static_cast<int>(_eyePos.y + window_pos.y - camera_pos.y),
			static_cast<int>(target_pos.x + window_pos.x - camera_pos.x),
			static_cast<int>(target_pos.y + window_pos.y - camera_pos.y),
			GetColor(255, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 30);
		for (auto&& grid : _eyelineGrids) {
			DrawBox(static_cast<int>(grid.first * 30 + window_pos.x - camera_pos.x),
				static_cast<int>(grid.second * 30 + window_pos.y - camera_pos.y),
				static_cast<int>(grid.first * 30 + 30 + window_pos.x - camera_pos.x),
				static_cast<int>(grid.second * 30 + 30 + window_pos.y - camera_pos.y),
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

	std::string head2path{ "resource/Enemy/2_head" };
	switch (pattern.head) {
	case 1:
	case 3:
	case 7:
	case 8:
		_cg_top2[EnemyDirection::Down]		= ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownLeft]	= ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::Left]		= ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpLeft]	= ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::Up]		= ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpRight]	= ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::Right]		= ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownRight] = ImageServer::LoadGraph("resource/Enemy/blank.png");
		break;
	case 2:
	case 4:
	case 5:
	case 6:
	case 9:
		_cg_top2[EnemyDirection::Down]		= ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::DownLeft]	= ImageServer::LoadGraph(head2path+ std::to_string(pattern.head)  + "/2.png");
		_cg_top2[EnemyDirection::Left]		= ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/3.png");
		_cg_top2[EnemyDirection::UpLeft]	= ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/4.png");
		_cg_top2[EnemyDirection::Up]		= ImageServer::LoadGraph("resource/Enemy/blank.png");
		_cg_top2[EnemyDirection::UpRight]	= ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/6.png");
		_cg_top2[EnemyDirection::Right]		= ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/7.png");
		_cg_top2[EnemyDirection::DownRight] = ImageServer::LoadGraph(head2path + std::to_string(pattern.head) + "/8.png");
		break;
	}
	std::string headpath{ "resource/Enemy/head" };
	_cg_top[EnemyDirection::Down]		= ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/1.png");
	_cg_top[EnemyDirection::DownLeft]	= ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/2.png");
	_cg_top[EnemyDirection::Left]		= ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/3.png");
	_cg_top[EnemyDirection::UpLeft]		= ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/4.png");
	_cg_top[EnemyDirection::Up]			= ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/5.png");
	_cg_top[EnemyDirection::UpRight]	= ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/6.png");
	_cg_top[EnemyDirection::Right]		= ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/7.png");
	_cg_top[EnemyDirection::DownRight]  = ImageServer::LoadGraph(headpath + std::to_string(pattern.head) + "/8.png");
	std::string bodypath{ "resource/Enemy/body" };
	_cg_mid[EnemyDirection::Down]		= ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/1.png");
	_cg_mid[EnemyDirection::DownLeft]	= ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/2.png");
	_cg_mid[EnemyDirection::Left]		= ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/3.png");
	_cg_mid[EnemyDirection::UpLeft]		= ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/4.png");
	_cg_mid[EnemyDirection::Up]			= ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/5.png");
	_cg_mid[EnemyDirection::UpRight]	= ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/6.png");
	_cg_mid[EnemyDirection::Right]		= ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/7.png");
	_cg_mid[EnemyDirection::DownRight]	= ImageServer::LoadGraph(bodypath + std::to_string(pattern.body) + "/8.png");

	std::string footpath{ "resource/Enemy/foot" };
	_cg_bot[EnemyDirection::Down]		= ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/1.png");
	_cg_bot[EnemyDirection::DownLeft]	= ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/2.png");
	_cg_bot[EnemyDirection::Left]		= ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/3.png");
	_cg_bot[EnemyDirection::UpLeft]		= ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/4.png");
	_cg_bot[EnemyDirection::Up]			= ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/5.png");
	_cg_bot[EnemyDirection::UpRight]	= ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/6.png");
	_cg_bot[EnemyDirection::Right]		= ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/7.png");
	_cg_bot[EnemyDirection::DownRight]	= ImageServer::LoadGraph(footpath + std::to_string(pattern.foot) + "/8.png");
}

Vector2 Enemy::CheckRoomPosition() {
	double x = floor((_collision.min.x + _collision.max.x) / 2.0 / (static_cast<double>(splitscreen_W)));
	double y = floor((_collision.min.y + _collision.max.y) / 2.0 / (static_cast<double>(screen_H)));
	return{ x,y };
}
