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

/*�G�l�~�[�f�[�^�\��*/
class EnemyData :public ObjectDataBase {
public:
	int patrolID{ -1 };
	int waitFrame{ -0 };
};

/*�G�l�~�[B�f�[�^�\��*/
class EnemyBData :public ObjectDataBase {
public:
	std::vector<int> Direction;//<����p�x
	std::vector<int> LookTime;//<�e�p�x�����鎞��
};

/*�G�l�~�[����o�H�f�[�^�\��*/
class EnemyPatrol :public ObjectDataBase {
public:
	std::vector<Vector2> PatrolPoints;
	bool TruckingMode{ false };
};

/*�T�[�o�[�f�[�^�\��*/
class ServerMachineData : public ObjectDataBase {
public:
	std::string Direction{ "up" };
	bool upperleft{false};
};

/*�񕜃A�C�e���f�[�^�\��*/
class HPItemData :public ObjectDataBase {
public:
};
/*�G�l�~�[�f�[�^�\��*/
class BulletItemData :public ObjectDataBase {
public:
};

/*���C�g�f�[�^�\��*/
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

/*�e���|�[�^�[(in)�f�[�^�\��*/
class teleporterData : public ObjectDataBase {
public:
	bool random{false};
	int tereortID{-1};
};

/*�e���|�[�^�[(out)�f�[�^�\��*/
class TeleporterOutData : public ObjectDataBase {
public:
	bool random{ false };
};

/*�o���A�f�[�^�\��*/
class BarrierData : public ObjectDataBase {
public:
	int blockPlayerNo{-1};
};

/*�X�C�b�`�f�[�^�\��*/
class SwitchData : public ObjectDataBase {
public:
	bool RedFlag{false};
	std::vector<int> links;
};

/*�X�C�b�`�G���A�f�[�^�\��*/
class SwitchAreaData : public ObjectDataBase {
public:
	std::vector<int> links;
};

/*Door�f�[�^�\��*/
class DoorData : public ObjectDataBase {
public:
	int PartNo{-1};
};

/*TNT�f�[�^�\��*/
class TNTData : public ObjectDataBase {
public:
	int CG{-1};
};

/*Mine�f�[�^�\��*/
class MineData : public ObjectDataBase {
public:
	int range{-1};
	int dir{-1};
};

/*ScreenPump�f�[�^�\��*/
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