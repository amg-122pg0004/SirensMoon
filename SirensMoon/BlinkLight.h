/*****************************************************************//**
 * \file   BlinkLight.h
 * \brief  �Ԃ��_�ł��郉�C�g�ł��B
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "LightBase.h"

class Game;
class ModeGame;
class Actor;

class BlinkLight :public LightBase {
public:
	BlinkLight(Game&, ModeGame&, Actor&);
	void Update()override;
private:

};
