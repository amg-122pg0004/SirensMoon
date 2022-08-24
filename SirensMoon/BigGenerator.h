#pragma once
#include "Gimmick.h"

class BigGenerator :public Gimmick {
public:
	BigGenerator(Game& game, ModeGame& mode, int ID,std::vector<bool> signal);
	void Update()override;
	void StandardRender(Vector2 window_pos, Vector2 camera_pos);

private:
	int _pattern;


	/*Generator���d�l����V�O�i���p�^�[��*/
	std::vector<bool> _signal;
};
