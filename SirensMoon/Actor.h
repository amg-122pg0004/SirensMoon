/*****************************************************************//**
 * \file   Actor.h
 * \brief  アクター（画面に表示される物体）の親クラスです。
 * 
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include "Game.h"
#include "Math.h"
class Game;

class Actor{
	public:

		enum class Type {
			Actor,
			Player,
			Enemy,
			Bullet
		};
		Actor(Game& game);
		~Actor();

		virtual void Update();
		virtual void Render();
		virtual void IsDead(return _dead;);

	protected:
		Game& _game;
		Vector2 _pos;
		bool _dead;

};

