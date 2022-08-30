#include "SignalLight.h"
#include "BigGenerator.h"

SignalLight::SignalLight(Game& game, ModeGame& mode, Actor& owner)
	:LightBase(game,mode,owner)
{
	_cg = ImageServer::LoadGraph("resource/Light/Light_5.png");
	_pos = _owner.GetPosition();
}

void SignalLight::Update(){
	_activate=dynamic_cast<BigGenerator&>(_owner).GetSignalActive();
}

void SignalLight::MaskRender(Vector2 window_pos, Vector2 camera_pos){
	if (_activate) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawRotaGraph2(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
			static_cast<int>(_pos.y + window_pos.y - camera_pos.y),
			static_cast<int>(_centerPos.x),
			static_cast<int>(_centerPos.y),
			_scale,
			_angle,
			_cg, 1, 0);
	}
}
