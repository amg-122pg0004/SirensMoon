#pragma once
#include <DxLib.h>
#include <vector>
#include "Game.h"
#include "Math.h"

class Darkness {
	public:
		Darkness(Game& game);
		/*�}�X�N�f�[�^�̍쐬*/
		int MakeDarkness();
		/*�}�X�N�f�[�^�̍X�V*/
		void Update();
		/*�}�X�N�f�[�^�̍폜*/
		void DeleteDarkness();

	private:
		Game& _game;
		int _cg;//�}�X�N�p�摜�擾�p
		int _alphaHandle;
};