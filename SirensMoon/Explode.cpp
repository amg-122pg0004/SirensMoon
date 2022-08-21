/*****************************************************************//**
 * \file   Explode.cpp
 * \brief  ダメージ判定を持つコリジョンクラス、エフェクトは別
 * 
 * \author 土居将太郎
 * \date   August 2022
 *********************************************************************/

#include "Explode.h"
#include "ModeGame.h"
#include "FX_Boom.h"

Explode::Explode(Game& game, ModeGame& mode, Vector2 pos) :Actor(game, mode)
, _lifetime{ 70 },_delay{10}
{
	_size = { 80,80 };
	_pos = pos-_size/2;
	_collision.min =	{-1,-1};
	_collision.max = { -1,-1 };

}

void Explode::Update(){
	--_delay;
	if (_delay == 0) {
		PlaySoundMem(SoundServer::Find("Explosion"), DX_PLAYTYPE_BACK);
		auto fxboom = std::make_unique<FX_Boom>(_game, _mode, _pos, _game.GetFrameCount());
		_mode.GetActorServer().Add(std::move(fxboom));
		_collision.min = _pos;
		_collision.max = _pos + _size;

	}

	--_lifetime;
	if (_lifetime < 0){
		_dead=true;
	}
}

void Explode::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
}

void Explode::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2(stageNum, window_pos, camera_pos);
}
