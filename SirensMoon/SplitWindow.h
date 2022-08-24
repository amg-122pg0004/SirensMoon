/*****************************************************************//**
 * \file   SplitWindow.h
 * \brief  ������ʓ��ւ̕`����s���N���X�ł�
 * 
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/

#pragma once
#include "Camera.h"
#include "ActorServer.h"
#include "Darkness.h"
#include "PlayerA.h"
#include "PlayerB.h"
#include "UIBase.h"

class Camera;
class Darkness;

class SplitWindow {
	public:
		SplitWindow(Game& _game,ModeGame& mode, int pos_x, int pos_y,int window_no);
		void Update();
		void Render();
		void Debug();
		void DamageEvent();
		std::unique_ptr<Camera>& GetCamera() { return _camera; }

		int GetRenderStage() { return _renderStage; }
		int GetWindowSize_W() {return _windowSize_W;}
		int GetWindowSize_H() { return _windowSize_H;}
		std::vector<std::unique_ptr<UIBase>>& GetUIServer(){return _ui; }
		Vector2 GetWindowPos() { return _windowPos; }

		int GetLightUp() { return _lightup; }

		int GetWindowNo() { return _windowNo; }

	private:
		/*���邢���ǂ���*/
		int _lightup;

		int	_windowSize_W;
		int _windowSize_H;
		Vector2 _windowPos;
		std::unique_ptr<Camera> _camera;
		Game& _game;
		ModeGame& _mode;

		std::unique_ptr<Darkness> _darkness;
		std::vector<std::unique_ptr<UIBase>> _ui;

		/*�Èŕ\���p�̃X�N���[���n���h��*/
		int _darknessScreen;
		/*������ʓ��ɒʏ탌���_�����O����X�N���[���n���h��*/
		int _normalScreen;

		int _windowNo;
		int _renderStage;
}; 