/*****************************************************************//**
 * \file   ProjectionLight.h
 * \brief  ��������ɕ��˂���悤�ȃ��C�g�ł��B
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "LightBase.h"

class Game;
class ModeGame;
class Actor;

class ProjectionLight :public LightBase {
	public:
		ProjectionLight(Game&,ModeGame&,Actor&);
		void Update()override;
	private:
		double _scaleStart;
		double _scaleMax;
		int _alphaStart;
		int _alphaMax;
};
