#pragma once
#include "Gimmick.h"

class BigGenerator :public Gimmick {
public:
	BigGenerator(Game& game, ModeGame& mode, int ID,std::vector<bool> signal);
	void Update()override;
	void Render();

private:
	int _pattern;

	/*Generatorが仕様するシグナルパターン*/
	std::vector<bool> _signal;
};
