#include "Explode.h"

Explode::Explode(Game& game, ModeGame& mode, Vector2 pos) :Actor(game, mode), _lifetime{ 60 }
{

	_cg = ImageServer::LoadGraph("resource/Gimmick/explode.png");
	_size = { 80,80 };
	_pos = pos-_size/2;
	_collision.min = _pos;
	_collision.max = _pos + _size;
	PlaySoundMem(SoundServer::Find("Explosion"), DX_PLAYTYPE_BACK);
}

void Explode::Update(){
	--_lifetime;
	if (_lifetime < 0){
		_dead=true;
	}
}

void Explode::StandardRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y)
		, _cg
		, 1);
}

void Explode::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	_collision.Draw2(stageNum, window_pos, camera_pos);
}
