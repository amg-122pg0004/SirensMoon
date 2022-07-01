/*****************************************************************//**
 * \file   SplitWindow.h
 * \brief  分割画面内への描画を行うクラスです
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#pragma once
#include "Game.h"
#include "Camera.h"
#include "ActorServer.h"

class Camera;

class SplitWindow {
	public:
		SplitWindow(Game&, int pos_x, int pos_y,int playernum);
		void Update();
		void Render();
		std::unique_ptr<Camera>& GetCamera() { return _camera; }

		int GetRenderStage() { return _renderStage; }
		int GetWindowSize_W() {return _windowSize_W;}
		int GetWindowSize_H() { return _windowSize_H;}

		void ChangeRenderStage(int changedelta);
	private:
		int	_windowSize_W;
		int _windowSize_H;
		Vector2 _windowPos;
		std::unique_ptr<Camera> _camera;
		Game& _game;

		int _playerNum;
		int _renderStage;
}; 
