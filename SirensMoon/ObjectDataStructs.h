#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Math.h"


class ObjectDataBase {
public:
	std::string ClassName;
	int ID{ -1 };
	Vector2 pos{0,0};
};

class PlayerData :public ObjectDataBase {
public:
	int Player{ -1 };
	double SpeedMax{ 6.0 };
	double Accelerate { 1.0};
	double Friction{ 0.9 };
};

/*エネミーデータ構造*/
class EnemyData :public ObjectDataBase {
public:
	int patrolID{ -1 };
	int waitFrame{ -0 };
};

/*エネミーBデータ構造*/
class EnemyBData :public ObjectDataBase {
public:
	std::vector<int> Direction;//<見る角度
	std::vector<int> LookTime;//<各角度を見る時間
};

/*エネミー巡回経路データ構造*/
class EnemyPatrol :public ObjectDataBase {
public:
	std::vector<Vector2> PatrolPoints;
	bool TruckingMode{ false };
};

/*サーバーデータ構造*/
class ServerMachineData : public ObjectDataBase {
public:
	std::string Direction{ "up" };
	bool upperleft{false};
};

/*回復アイテムデータ構造*/
class HPItemData :public ObjectDataBase {
public:
};
/*エネミーデータ構造*/
class BulletItemData :public ObjectDataBase {
public:
};

/*ライトデータ構造*/
class SquareLightStats :public ObjectDataBase {
public:
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
	bool random{false};
	int tereortID{-1};
};

/*テレポーター(out)データ構造*/
class TeleporterOutData : public ObjectDataBase {
public:
	bool random{ false };
};

/*バリアデータ構造*/
class BarrierData : public ObjectDataBase {
public:
	int blockPlayerNo{-1};
};

/*スイッチデータ構造*/
class SwitchData : public ObjectDataBase {
public:
	bool RedFlag{false};
	std::vector<int> links;
};

/*スイッチエリアデータ構造*/
class SwitchAreaData : public ObjectDataBase {
public:
	std::vector<int> links;
};

/*Doorデータ構造*/
class DoorData : public ObjectDataBase {
public:
	int PartNo{-1};
};

/*TNTデータ構造*/
class TNTData : public ObjectDataBase {
public:
	int CG{-1};
};

/*Mineデータ構造*/
class MineData : public ObjectDataBase {
public:
	int range{-1};
	int dir{-1};
};

/*ScreenPumpデータ構造*/
class ScreenPumpData : public ObjectDataBase {
public:
	int range{180};
	int dir{-1};
};

/*StickyBomb*/
class StickyBombData : public ObjectDataBase {
public:
	int range{180};
	int timer{-1};
};


class BreakableObjectData : public ObjectDataBase{
public:
};

class DigitalLetterData : public ObjectDataBase {
public:
	std::string message{};
};

class BigServerData : public ObjectDataBase {
public:
	std::string Direction{};
};

class BigGeneratorData : public ObjectDataBase {
public:
};

class BigGunData :public ObjectDataBase {
public:
};

class BossGimmickControllerData:public ObjectDataBase {
public:
	int gunID{-1};
	int teleporterID{-1};
	std::vector<int> serversID;
	std::vector<int> generatorsID;
};