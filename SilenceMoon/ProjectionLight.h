/*****************************************************************//**
 * \file   ProjectionLight.h
 * \brief  特定方向に放射するようなライトです。
 * 
 * \author 土居将太郎
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
