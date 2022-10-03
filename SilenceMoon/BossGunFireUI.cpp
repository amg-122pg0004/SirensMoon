/*****************************************************************//**
 * \file   BossGunFireUI.cpp
 * \brief  �{�X�̍U�������킷���Ƃ𑣂�UI
 * 
 * \author amg
 * \date   September 2022
 *********************************************************************/

#include "BossGunFireUI.h"
#include "Game.h"
#include "ModeBase.h"
#include "SplitWindow.h"

BossGumFireUI::BossGumFireUI(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase(game, mode, window, pos, size), _lifetime{ 200 }
{
	_cg = ImageServer::LoadGraph("resource/UI/Info/BossGunFireUI.png");
}

void BossGumFireUI::Update() {
	--_lifetime;
	if (_lifetime < 0) {
		_dead = true;
	}
}

void BossGumFireUI::Render() {
	DrawRotaGraph(_pos.x,_pos.y,1.0,0.0,_cg,1);
}
