/*****************************************************************//**
 * \file   BossGunFireUI.cpp
 * \brief  É{ÉXÇÃçUåÇÇÇ©ÇÌÇ∑Ç±Ç∆Çë£Ç∑UI
 * 
 * \author amg
 * \date   September 2022
 *********************************************************************/

#include "BossGunFireUI.h"
#include "Game.h"
#include "ModeBase.h"
#include "SplitWindow.h"

BossGumFireUI::BossGumFireUI(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase(game, mode, window, pos, size)
{
	_cg = ImageServer::LoadGraph("resource/UI/Info/OpenMinimapInfo.png");
}

void BossGumFireUI::Update() {

}

void BossGumFireUI::Render() {
	DrawRotaGraph(_pos.x,_pos.y,1.0,0.0,_cg,1);
}
