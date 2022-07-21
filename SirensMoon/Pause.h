/*****************************************************************//**
 * \file   Pause.h
 * \brief  ポーズ画面を表示するUIです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "UIBase.h"
#include "Math.h"
#include <memory>

class Game;
class ModeBase;
class InputManager;

class Pause :public UIBase{
	public:
		Pause(Game& game, ModeBase& mode, Vector2 pos, Vector2 size);
		void Update() override;
		void Render() override ;
	private:
		std::shared_ptr<InputManager> _inputManager;
		int _cg;
};