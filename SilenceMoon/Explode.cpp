/*****************************************************************//**
 * \file   Explode.cpp
 * \brief  ダメージ判定を持つコリジョン用クラス
 * 
 * \author 土居将太郎
 * \date   August 2022
 *********************************************************************/

#include "Explode.h"
#include "ModeGame.h"
#include "FX_Boom.h"
#include "FX_HeadButt.h"

Explode::Explode(Game& game, ModeGame& mode, Vector2 pos) :Actor(game, mode)
, _lifetime{ 70 },_delay{1}
{
	_size = { 80,80 };
	_pos = pos-_size/2;
	_collision.min =	{-1,-1};
	_collision.max = { -1,-1 };
	StartJoypadVibration(DX_INPUT_PAD1, 500, 150, -1);
	StartJoypadVibration(DX_INPUT_PAD2, 500, 150, -1);
}

void Explode::Update(){
	--_delay;
	if (_delay == 0) {
		PlaySoundMem(SoundServer::Find("Explosion"), DX_PLAYTYPE_BACK);
		auto fxboom = std::make_unique<FX_Boom>(_game, _mode, _pos+_size/2, _game.GetFrameCount());
		_mode.GetActorServer().Add(std::move(fxboom));
		_collision.min = _pos;
		_collision.max = _pos + _size;

	}

	--_lifetime;
	if (_lifetime < 0){
		_dead=true;
	}
}

void Explode::StandardRender(Vector2 window_pos, Vector2 camera_pos) {

}

void Explode::Debug(Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2(window_pos, camera_pos);
}


Explode2::Explode2(Game& game, ModeGame& mode, Vector2 pos) :Actor(game, mode)
, _lifetime{ 70 }, _delay{ 10 }
{
	_size = { 250,250 };
	_pos = pos - _size / 2;
	_collision.min = { -1,-1 };
	_collision.max = { -1,-1 };
	StartJoypadVibration(DX_INPUT_PAD1, 500, 150, -1);
	StartJoypadVibration(DX_INPUT_PAD2, 500, 150, -1);

}

void Explode2::Update() {
	--_delay;
	if (_delay == 0) {
		auto fxboom = std::make_unique<FX_Boom2>(_game, _mode, _pos+_size/2, _game.GetFrameCount());
		_mode.GetActorServer().Add(std::move(fxboom));
		_collision.min = _pos;
		_collision.max = _pos + _size;
	}

	--_lifetime;
	if (_lifetime < 0) {
		_dead = true;
	}
}

void Explode2::StandardRender(Vector2 window_pos, Vector2 camera_pos) {

}

void Explode2::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(window_pos, camera_pos);
}


Explode3::Explode3(Game& game, ModeGame& mode, Vector2 pos) :Actor(game, mode)
, _lifetime{ 70 }, _delay{ 1 }
{
	_size = { 200,200 };
	_pos = pos - _size / 2;
	_collision.min = { -1,-1 };
	_collision.max = { -1,-1 };
	StartJoypadVibration(DX_INPUT_PAD1, 500, 150, -1);
	StartJoypadVibration(DX_INPUT_PAD2, 500, 150, -1);

}

void Explode3::Update() {
	--_delay;
	if (_delay == 0) {
		auto fxboom = std::make_unique<FX_HeadButt>(_game, _mode, _pos + _size / 2, _game.GetFrameCount());
		_mode.GetActorServer().Add(std::move(fxboom));
		_collision.min = _pos;
		_collision.max = _pos + _size;
	}

	--_lifetime;
	if (_lifetime < 0) {
		_dead = true;
	}
}

void Explode3::StandardRender(Vector2 window_pos, Vector2 camera_pos) {

}

void Explode3::Debug(Vector2 window_pos, Vector2 camera_pos) {
	_collision.Draw2(window_pos, camera_pos);
}
