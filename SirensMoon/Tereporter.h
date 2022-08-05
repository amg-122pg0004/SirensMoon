#pragma once
#include "Actor.h"
#include "MapChip.h"

class Game;
class ModeGame;

class TereporterIn :public Actor{
public:
	TereporterIn(Game& game, ModeGame& mode, MapChips::TereporterData data);
	Type GetType()override { return Type::Tereporter; }

	void Update()override;

	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;
	void Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

	int GetTereportID() { return _tereportID; }
	bool GetRandomFlag() { return _randomFlag; }

private:
	int _tereportID;
	bool _randomFlag;
};

class TereporterOut :public Actor {
public:
	TereporterOut(Game& game, ModeGame& mode, Vector2 data);
	Type GetType()override { return Type::Tereporter; }

	void StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos)override;

private:
};
