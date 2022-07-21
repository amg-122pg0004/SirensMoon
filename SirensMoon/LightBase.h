/*****************************************************************//**
 * \file   LightBase.h
 * \brief  光（マスク画像）の親クラスです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include "Math.h"
#include "ModeBase.h"

class Actor;
class Game;

class LightBase:public Actor  {
	public:

		LightBase(Game& game,ModeBase& mode,Actor& owner);
		void Update();

		Actor::Type GetType()override { return Type::Light; };
		int GetGrHandle() { return _cg; }
		Vector2 GetCenterPosition() { return _centerPos; }
		double GetAngle() { return _angle; }
		double GetScale() { return _scale; }

		void CheckDeadOwner()override;

	protected:
		Actor& _owner;
		int _cg;
		Vector2 _centerPos;
		double _angle;
		double _scale;
};

