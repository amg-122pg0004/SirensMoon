/*****************************************************************//**
 * \file   Camera.h
 * \brief  �I�u�W�F�N�g�������_�����O����ۂ̊�_�Ƃ��Ďg�p
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/
#pragma once
#include "Game.h"
#include "SplitWindow.h"
#include <memory>
#include <sstream>

class Game;
class ModeBase;
class SplitWindow;

class Camera {
	public:
		Camera(Game&game,ModeBase& mode,SplitWindow&sw);
		void Update(int playernum);//<�J�����̈ړ�
		Vector2 GetPosition() { return _pos; }//<�J�������W�̎擾
		//void Render(int x, int y);
		enum class ChangeDir {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		void ChangePosition(ChangeDir direction);
		void SetPosition(Vector2 playerpos);

		
#ifdef _DEBUG
		void Render(int x,int y);//�J�����̈ʒu���W�\��
#endif
	private:
		Game& _game;//<Game�Q��
		ModeBase& _mode;
		SplitWindow& _splitWindow; //<SplitWindow�Q��
		std::shared_ptr<InputManager> _inputManager;//<InputManager�̎Q��
		int _speed;//<�J�����̈ړ����x
		Vector2 _pos;//<�J�����̈ʒu���W
		Vector2 _stageSize;//<�X�e�[�W�̑傫��
};
