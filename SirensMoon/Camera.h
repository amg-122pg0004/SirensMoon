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

class Game;
class SplitWindow;

class Camera {
	public:
		Camera(Game&game,SplitWindow&sw);
		void Update(int playernum);//<�J�����̈ړ�
		Vector2 GetCameraPosition() { return _cameraPosition; }//<�J�������W�̎擾
		
#ifdef _DEBUG
		void Render(int x,int y);//�J�����̈ʒu���W�\��
#endif
	private:
		Game& _game;//<Game�Q��
		SplitWindow& _splitWindow; //<SplitWindow�Q��
		std::shared_ptr<InputManager> _inputManager;//<InputManager�̎Q��
		int _speed;//<�J�����̈ړ����x
		Vector2 _cameraPosition;//<�J�����̈ʒu���W
};
