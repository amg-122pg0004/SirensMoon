#include "SignalLight.h"
#include "BigGenerator.h"

SignalLight::SignalLight(Game& game, ModeGame& mode, Actor& owner)
	:LightBase(game,mode,owner)
{

}

void SignalLight::Update(){
	_activate=dynamic_cast<BigGenerator&>(_owner).GetActivate();
}

void SignalLight::MaskRender(Vector2 window_pos, Vector2 camera_pos){
	if (_activate) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawRotaGraph2(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
			static_cast<int>(_centerPos.x),
			static_cast<int>(_centerPos.y),
			_scale,
			_angle,
			_cg, 1, 0);
	}
}
