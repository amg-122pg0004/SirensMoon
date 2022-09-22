/*****************************************************************//**
 * \file   LightBase.h
 * \brief  ���i�}�X�N�摜�j�̐e�N���X�ł��B
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include "Math.h"
#include "Actor.h"

class ModeGame;
class Game;

class LightBase:public Actor  {
	public:

		LightBase(Game& game,ModeGame& mode,Actor& owner);
		void Update();
		virtual void MaskRender(Vector2 window_pos,Vector2 camera_pos);

		Actor::Type GetType()override { return Type::Light; };
		int GetGrHandle() { return _cg; }
		Vector2 GetCenterPosition() { return _centerPos; }
		double GetAngle() { return _angle; }
		double GetScale() { return _scale; }
		int GetAlpha() { return _alpha; }

		Actor& GetOwner() { return _owner; }

		void CheckDeadOwner()override;

	protected:

		Actor& _owner;
		int _cg;
		Vector2 _centerPos;
		double _angle;
		double _scale;
		int _alpha;
		bool _activate;
};

