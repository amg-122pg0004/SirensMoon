#pragma once
//#include "EnemyB.h"
//
//class EnemyB:public Actor{
//public:
//	EnemyB(Game& game, ModeGame& mode, ObjectDataStructs::EnemyBData enemydata, EnemyGenerator::EnemyGrData grdata);
//
//	void Update();
//
//	/*視界判定を更新*/
//	void  SightUpdate();
//	/*視界内にプレイヤーが居るか判定*/
//	bool CheckDetection();
//
//	/*弾、プレイヤーと触れているか確認する*/
//	virtual void CheckDamage();
//	/*プレイヤーへ接近する*/
//	void MoveToPlayer();
//	/*プレイヤーにダメージを与える*/
//	void ApplyDamage();
//	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos) override;
//
//	void UpdateCollision();
//	void AnimationUpdate();
//
//private:
//	/*視界判定*/
//	class BoxSight {
//	public:
//		Vector2 pos1, pos2, pos3, pos4;//<敵視点から手前左右、奥左右
//	};
//
//	void Init();
//
//
//	/*向いている方向*/
//	Vector2 _dir;
//
//	BoxSight _sightPos;
//	/*眼の位置*/
//	Vector2 _eyePos;
//
//	/*追跡フラグ*/
//	bool _chase;
//	/*視界範囲*/
//	const int _sight_H, _sight_W;
//	/*視界範囲内にいたフレーム数*/
//	int _detectionFrame;
//	/*最後に発見した物体*/
//	Actor* _lastDetection;
//
//
//	ObjectDataStructs::EnemyBData _data;
//
//	/*Enemyランダム生成パターン*/
//	std::vector<int> _generatedEnemy;
//	/*Enemy仮画像*/
//	std::map<EnemyGenerator::EnemyDirection, int> _cg_top;
//	std::map<EnemyGenerator::EnemyDirection, int> _cg_mid;
//	std::map<EnemyGenerator::EnemyDirection, int> _cg_top2;
//	std::map<EnemyGenerator::EnemyDirection, int> _cg_bot;
//
//	EnemyGenerator::EnemyDirection _cg_direction;
//	int _animeNo;//<アニメーションの表示番号
//};
