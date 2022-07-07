/*****************************************************************//**
 * \file   Camera.h
 * \brief  オブジェクトをレンダリングする際の基準点として使用
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/
#pragma once
#include "Game.h"
#include "SplitWindow.h"
#include <memory>

class Game;
class SplitWindow;

class Camera {
	public:
		Camera(Game&game,SplitWindow&sw);
		void Update(int playernum);//<カメラの移動
		Vector2 GetCameraPosition() { return _pos; }//<カメラ座標の取得

		enum class ChangeDir {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		void ChangePosition(ChangeDir direction);

		
#ifdef _DEBUG
		void Render(int x,int y);//カメラの位置座標表示
#endif
	private:
		Game& _game;//<Game参照
		SplitWindow& _splitWindow; //<SplitWindow参照
		std::shared_ptr<InputManager> _inputManager;//<InputManagerの参照
		int _speed;//<カメラの移動速度
		Vector2 _pos;//<カメラの位置座標
		Vector2 _stageSize;//<ステージの大きさ
};
