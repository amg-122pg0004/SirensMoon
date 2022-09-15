#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Math.h"


class ObjectDataBase {
public:
	enum class Type {
		Player,
		Enemy,
		EnemyB,
		EnemyPatrol,
		Light,
		AmmoItem,
		HPItem,
		Server,
		Barrirer,
		BossGenerator,
		BossRailGun,
		BossServer,
		BossTrigger,
		BreakableObject,
		DigitalLetter,
		Door,
		Mine,
		ScreenPump,
		StickeyBomb,
		Switch,
		SwitchArea,
		Teleport_IN,
		Teleport_OUT,
		TNT
	};
	virtual Type GetType() = 0;
	int ID{ -1 };
	Vector2 pos{0,0};
};

class PlayerData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Player; }
	int Player{ -1 };
	double SpeedMax{ 6.0 };
	double Accelerate { 1.0};
	double Friction{ 0.9 };
	double SlowSpeedRate{ 0.1 };
};

/*エネミーデータ構造*/
class EnemyData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Enemy; }
	int patrolID{ -1 };
	int waitFrame{ -0 };
	int sightW{ 330 };
	int sightH{ 210 };
	int detectionComplete{ 120 };
};

/*エネミーBデータ構造*/
class EnemyBData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::EnemyB; }
	std::vector<int> Direction{0,0,0,0};//<見る角度
	std::vector<int> LookTime{ 0,0,0,0 };//<各角度を見る時間
	int sightW{ 330 };
	int sightH{ 210 };
	int detectionComplete{ 120 };
};

/*エネミー巡回経路データ構造*/
class EnemyPatrol :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::EnemyPatrol; }
	std::vector<Vector2> PatrolPoints;
	bool TruckingMode{ false };
};

/*サーバーデータ構造*/
class ServerMachineData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Server; }
	std::string Direction{ "up" };
	bool upperleft{false};
};

/*回復アイテムデータ構造*/
class HPItemData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::HPItem; }
};
/*エネミーデータ構造*/
class BulletItemData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::AmmoItem; }
};

/*ライトデータ構造*/
class SquareLightStats :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Light; }
	std::string object{ "NULL" };
	std::string image{ "resource/Light/Light_square.png" };
	bool activate{ true };
	Vector2 pos{ 0,0 };
	Vector2 size{ 100,100 };
	int r{ 255 };
	int g{ 255 };
	int b{ 255 };
	int alpha{ 100 };
};

/*テレポーター(in)データ構造*/
class teleporterData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Teleport_IN; }
	bool random{false};
	int tereortID{-1};
};

/*テレポーター(out)データ構造*/
class TeleporterOutData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Teleport_OUT; }
	bool random{ false };
};

/*バリアデータ構造*/
class BarrierData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Barrirer; }
	int blockPlayerNo{-1};
};

/*スイッチデータ構造*/
class SwitchData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Switch; }
	bool RedFlag{false};
	std::vector<int> links;
	int projectionNumber{12};
};

/*スイッチエリアデータ構造*/
class SwitchAreaData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::SwitchArea; }
	std::vector<int> links;
};

/*Doorデータ構造*/
class DoorData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Door; }
	int PartNo{-1};
};

/*TNTデータ構造*/
class TNTData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::TNT; }
	int CG{-1};
};

/*Mineデータ構造*/
class MineData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Mine; }
	int range{180};
	int dir{-1};
};

/*ScreenPumpデータ構造*/
class ScreenPumpData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::ScreenPump; }
	int range{180};
	int dir{-1};
};

/*StickyBomb*/
class StickyBombData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::StickeyBomb; }
	int range{180};
	int timer{-1};
};


class BreakableObjectData : public ObjectDataBase{
public:
	Type GetType()override { return ObjectDataBase::Type::BreakableObject; }
};

class DigitalLetterData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::DigitalLetter; }
	std::string message{};
};

class BigServerData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::BossServer; }
	std::string Direction{};
};

class BigGeneratorData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::BossGenerator; }
};

class BigGunData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::BossRailGun; }
};

class BossGimmickControllerData:public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::BossTrigger; }
	int gunID{-1};
	int teleporterID{-1};
	std::vector<int> serversID;
	std::vector<int> generatorsID;
};