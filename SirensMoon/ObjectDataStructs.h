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

/*�G�l�~�[�f�[�^�\��*/
class EnemyData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Enemy; }
	int patrolID{ -1 };
	int waitFrame{ -0 };
	int sightW{ 330 };
	int sightH{ 210 };
	int detectionComplete{ 120 };
};

/*�G�l�~�[B�f�[�^�\��*/
class EnemyBData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::EnemyB; }
	std::vector<int> Direction{0,0,0,0};//<����p�x
	std::vector<int> LookTime{ 0,0,0,0 };//<�e�p�x�����鎞��
	int sightW{ 330 };
	int sightH{ 210 };
	int detectionComplete{ 120 };
};

/*�G�l�~�[����o�H�f�[�^�\��*/
class EnemyPatrol :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::EnemyPatrol; }
	std::vector<Vector2> PatrolPoints;
	bool TruckingMode{ false };
};

/*�T�[�o�[�f�[�^�\��*/
class ServerMachineData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Server; }
	std::string Direction{ "up" };
	bool upperleft{false};
};

/*�񕜃A�C�e���f�[�^�\��*/
class HPItemData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::HPItem; }
};
/*�G�l�~�[�f�[�^�\��*/
class BulletItemData :public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::AmmoItem; }
};

/*���C�g�f�[�^�\��*/
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

/*�e���|�[�^�[(in)�f�[�^�\��*/
class teleporterData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Teleport_IN; }
	bool random{false};
	int tereortID{-1};
};

/*�e���|�[�^�[(out)�f�[�^�\��*/
class TeleporterOutData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Teleport_OUT; }
	bool random{ false };
};

/*�o���A�f�[�^�\��*/
class BarrierData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Barrirer; }
	int blockPlayerNo{-1};
};

/*�X�C�b�`�f�[�^�\��*/
class SwitchData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Switch; }
	bool RedFlag{false};
	std::vector<int> links;
	int projectionNumber{12};
};

/*�X�C�b�`�G���A�f�[�^�\��*/
class SwitchAreaData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::SwitchArea; }
	std::vector<int> links;
};

/*Door�f�[�^�\��*/
class DoorData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Door; }
	int PartNo{-1};
};

/*TNT�f�[�^�\��*/
class TNTData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::TNT; }
	int CG{-1};
};

/*Mine�f�[�^�\��*/
class MineData : public ObjectDataBase {
public:
	Type GetType()override { return ObjectDataBase::Type::Mine; }
	int range{180};
	int dir{-1};
};

/*ScreenPump�f�[�^�\��*/
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