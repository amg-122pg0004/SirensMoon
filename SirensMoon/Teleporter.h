#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class Game;
class ModeGame;

class teleporterIn :public Gimmick {
public:
	teleporterIn(Game& game, ModeGame& mode, int ID, teleporterData data);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::Teleporter; }

	void Update()override;

	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(Vector2 window_pos, Vector2 camera_pos)override;

	int GetteleportID() { return _teleportID; }
	bool GetRandomFlag() { return _randomFlag; }

private:
	int _teleportID;
	bool _randomFlag;
};

class teleporterOut :public Gimmick {
public:
	teleporterOut(Game& game, ModeGame& mode,TeleporterOutData data);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::Teleporter; }
	void Update()override;

	void StandardRender(Vector2 window_pos, Vector2 camera_pos)override;

private:
	AABB _openCollision;
	bool _open;
	int _cg2;
};
