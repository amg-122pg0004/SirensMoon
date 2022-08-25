#pragma once
#include "Gimmick.h"
#include "ObjectDataStructs.h"

class BigGenerator :public Gimmick {
public:
	BigGenerator(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data,std::vector<bool> signal);
	Type GetType()override { return Type::Gimmick; }
	GimmickType GetGimmickType()override { return GimmickType::BigGenerator; }
	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos);
	bool GetSignalActive() { return _active; };

private:
	bool _active;//<発光するタイミング

	/*単符表示フレーム数*/
	int _span;
	/*現在の表示フレーム数*/
	int _elapsed;

	/*現在表示中のシグナル項番*/
	int _index;
	/*Generatorが仕様するシグナルパターン*/
	std::vector<bool> _signal;
};
