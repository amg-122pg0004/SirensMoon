/*****************************************************************//**
 * \file   BlinkLight.h
 * \brief  赤い点滅するライトです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "LightBase.h"

class Game;
class ModeBase;
class Actor;

class BlinkLight :public LightBase {
public:
	BlinkLight(Game&, ModeBase&, Actor&);
	void Update()override;
private:

};
