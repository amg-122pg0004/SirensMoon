#pragma once
#include <DxLib.h>
#include <vector>
#include "Game.h"
#include "Math.h"

class SplitWindow;

class Darkness {
	public:
		Darkness(Game& game,SplitWindow& splitwindow);
		/*�}�X�N�f�[�^�̍쐬*/
		int MakeDarkness();
		/*�}�X�N�f�[�^�̍X�V*/
		void Update(Vector2 window_pos, Vector2 camera_pos);
		/*�}�X�N�f�[�^�̍폜*/
		void DeleteDarkness();

	private:
		Game& _game;
		SplitWindow& _splitWindow;

		int _cg;//�}�X�N�p�摜�擾�p
		int _alphaHandle;
};