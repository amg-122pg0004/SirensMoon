#include "SquareLight.h"
#include "Enemy.h"
#include "Game.h"
#include <math.h>
#include "FloorLamp.h"

SquareLight::SquareLight(Game& game, ModeGame& mode, Actor& owner, SquareLightStats stats)
	:LightBase{ game,mode,owner }
{
	
	_cg = ImageServer::LoadGraph(stats.image);

	_pos = stats.pos;
	_size = stats.size;
	_r = stats.r;
	_g = stats.g;
	_b = stats.b;
	_alpha = stats.alpha;

	_scale = 1.0;
}

void SquareLight::Update() {
	_activate = dynamic_cast<Gimmick&>(_owner).GetActivate();
}

void SquareLight::MaskRender(Vector2 window_pos, Vector2 camera_pos) {
	if (_activate) {
		SetDrawBright(_r, _g, _b);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawExtendGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
			static_cast<int>(_pos.x + _size.x + window_pos.x - camera_pos.x),
			static_cast<int>(_pos.y + _size.y + window_pos.y - camera_pos.y),
			_cg, 1);

		SetDrawBright(255, 255, 255);
	}
}

