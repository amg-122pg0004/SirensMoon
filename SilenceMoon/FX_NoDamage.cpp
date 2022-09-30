/*****************************************************************//**
 * \file   FX_Thunder.cpp
 * \brief  雷エフェクト
 *
 * \author 土居将太郎
 * \date   September 2022
 *********************************************************************/
#include "FX_NoDamage.h"
#include "Easing.h"

FX_NoDamage::FX_NoDamage(Game& game, ModeGame& mode, const Vector2& pos, int startTime)
	:Effect(game, mode, pos, startTime)
{
	_cg.resize(16);
	ImageServer::LoadDivGraph("resource/Effect/thunder2.png", 16, 8, 2, 480, 270, _cg.data());
	_zoom = 2.0;
	_lifeTime = 20;
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FX_NoDamage::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_animNo = linear(elapsed, 0, static_cast<int>(_cg.size()), _lifeTime);
}

void FX_NoDamage::StandardRender(Vector2 window_pos, Vector2 camera_pos){
	SetDrawBlendMode(_blendMode, static_cast<int>(_alpha));
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	GraphFilter(_cg[_animNo], DX_GRAPH_FILTER_HSB, 0, 240, 0, 0);
	int x = static_cast<int>(_pos.x - camera_pos.x + window_pos.x);
	int y = static_cast<int>(_pos.y - camera_pos.y + window_pos.y);

	DrawRotaGraph(x, y, _zoom, _angle, _cg[_animNo], true, false);

	GraphFilter(_cg[_animNo], DX_GRAPH_FILTER_HSB, 0, 0, 0, 0);
	SetDrawMode(DX_DRAWMODE_NEAREST);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
