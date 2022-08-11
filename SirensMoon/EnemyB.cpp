//#include "EnemyB.h"
//#include "Enemy.h"
//#include "ImageServer.h"
//#include "SoundServer.h"
//#include "ModeGame.h"
//#include "BlinkLight.h"
//
//
//EnemyB::EnemyB(Game& game, ModeGame& mode, ObjectDataStructs::EnemyBData enemydata, EnemyGenerator::EnemyGrData grdata)
//	:Actor{game,mode}
//{
//	
//
//	_generatedEnemy.emplace_back(grdata.pattern.head);
//	_generatedEnemy.emplace_back(grdata.pattern.body);
//	_generatedEnemy.emplace_back(grdata.pattern.foot);
//
//	_cg_top = grdata.head;
//	_cg_top2 = grdata.head2;
//	_cg_mid = grdata.body;
//	_cg_bot = grdata.foot;
//}
//
//void EnemyB::Update(){
//
//}
//
//void EnemyB::Init() {
//
//}
//
//void EnemyB::SightUpdate() {
//	_eyePos = _pos + _size / 2;
//	auto fov = _eyePos + _dir * _sight_W;
//	Vector2 dirside = { _dir.y * -1,_dir.x };//<視界に垂直なベクトル
//	/*視界範囲4点作成*/
//	_sightPos.pos1 = { _eyePos.x - dirside.x * (_sight_H / 2),_eyePos.y - dirside.y * (_sight_H / 2) };
//	_sightPos.pos2 = { _eyePos.x + dirside.x * (_sight_H / 2),_eyePos.y + dirside.y * (_sight_H / 2) };
//	_sightPos.pos3 = { (_eyePos + _dir * _sight_W).x - dirside.x * (_sight_H / 2),(_eyePos + _dir * _sight_W).y - dirside.y * (_sight_H / 2) };
//	_sightPos.pos4 = { (_eyePos + _dir * _sight_W).x + dirside.x * (_sight_H / 2),(_eyePos + _dir * _sight_W).y + dirside.y * (_sight_H / 2) };
//}
//
//bool EnemyB::CheckDetection() {
//	for (auto&& actor : _mode.GetActorServer().GetObjects()) {
//		if (actor->GetType() == Type::PlayerA || actor->GetType() == Type::PlayerB) {
//			CheckRoomPosition();
//			if (_roomPosition.x == actor->GetRoomPosition().x && _roomPosition.y == actor->GetRoomPosition().y) {
//				auto col = actor->GetCollision();
//				Vector2 righttop = { col.max.x,col.min.y };
//				Vector2 leftbottom = { col.min.x,col.max.y };
//
//				AABB enemyaround = { {0,0},{0,0} };
//				enemyaround.min = { _eyePos.x - 60,_eyePos.y - 75 };
//				enemyaround.max = { _eyePos.x + 60,_eyePos.y + 75 };
//				/*周辺判定*/
//				if (Intersect(enemyaround, col)) {
//					_lastDetection = actor.get();
//					return 1;
//				}
//				/*pos1,pos2は周辺判定の範囲に含まれるため判定を行わない*/
//				/*pos2,pos4とプレイヤーコリジョン4辺*/
//				if (Vector2::IsCrossed(_sightPos.pos2, _sightPos.pos4, col.min, righttop) ||
//					Vector2::IsCrossed(_sightPos.pos2, _sightPos.pos4, righttop, col.max) ||
//					Vector2::IsCrossed(_sightPos.pos2, _sightPos.pos4, col.max, leftbottom) ||
//					Vector2::IsCrossed(_sightPos.pos2, _sightPos.pos4, leftbottom, col.min)) {
//					_lastDetection = actor.get();
//					return 1;
//				}
//				/*pos1,pos3とプレイヤーコリジョン4辺*/
//				if (Vector2::IsCrossed(_sightPos.pos1, _sightPos.pos3, col.min, righttop) ||
//					Vector2::IsCrossed(_sightPos.pos1, _sightPos.pos3, righttop, col.max) ||
//					Vector2::IsCrossed(_sightPos.pos1, _sightPos.pos3, col.max, leftbottom) ||
//					Vector2::IsCrossed(_sightPos.pos1, _sightPos.pos3, leftbottom, col.min)) {
//					_lastDetection = actor.get();
//					return 1;
//				}
//				/*pos3,pos4とプレイヤーコリジョン4辺*/
//				if (Vector2::IsCrossed(_sightPos.pos3, _sightPos.pos4, col.min, righttop) ||
//					Vector2::IsCrossed(_sightPos.pos3, _sightPos.pos4, righttop, col.max) ||
//					Vector2::IsCrossed(_sightPos.pos3, _sightPos.pos4, col.max, leftbottom) ||
//					Vector2::IsCrossed(_sightPos.pos3, _sightPos.pos4, leftbottom, col.min)) {
//					_lastDetection = actor.get();
//					return 1;
//				}
//				/*視界内に完全に納まっている場合の確認*/
//				if (Vector2::Cross(_sightPos.pos1 - _sightPos.pos3, col.min - _sightPos.pos3) < 0 &&
//					Vector2::Cross(_sightPos.pos3 - _sightPos.pos4, col.min - _sightPos.pos4) < 0 &&
//					Vector2::Cross(_sightPos.pos4 - _sightPos.pos2, col.min - _sightPos.pos2) < 0 &&
//					Vector2::Cross(_sightPos.pos2 - _sightPos.pos1, col.min - _sightPos.pos1) < 0) {
//					_lastDetection = actor.get();
//					return 1;
//				}
//			}
//		}
//	}
//	return 0;
//}