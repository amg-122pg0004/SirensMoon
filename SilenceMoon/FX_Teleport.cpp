/*****************************************************************//**
 * \file   FX_Teleport.cpp
 * \brief  テレポートエフェクト
 * 
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include"FX_Teleport.h"
#include "Easing.h"


FX_TeleportIN1::FX_TeleportIN1(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/teleport_inR.png", 68, 4, 17, 128, 128, _cg.data());

	_zoom = 1.0;
	_lifeTime = 68 * 1;
	_blendMode = DX_BLENDMODE_ALPHA;
}
void FX_TeleportIN1::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = static_cast<int>(linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime));
}

FX_TeleportIN2::FX_TeleportIN2(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/teleport_inB.png", 68, 4, 17, 128, 128, _cg.data());

	_zoom = 1.0;
	_lifeTime = 68 * 1;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_TeleportIN2::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = static_cast<int>(linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime));
}

FX_TeleportOUT1::FX_TeleportOUT1(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/teleport_outR.png", 68, 4, 17, 128, 128, _cg.data());

	_zoom = 1.0;
	_lifeTime = 68 * 1;
	_blendMode = DX_BLENDMODE_ALPHA;
}
void FX_TeleportOUT1::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);
}

FX_TeleportOUT2::FX_TeleportOUT2(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(112);
	ImageServer::LoadDivGraph("resource/Effect/teleport_outB.png", 68, 4, 17, 128, 128, _cg.data());

	_zoom = 1.0;
	_lifeTime = 68 * 1;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_TeleportOUT2::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);
}