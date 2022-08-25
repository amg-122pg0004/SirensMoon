#include "BigGenerator.h"
#include "SignalLight.h"
#include "ModeGame.h"
#include <sstream>

BigGenerator::BigGenerator(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data, std::vector<bool> signal)
	:Gimmick(game,mode,data.ID),_signal{signal},_span{20},_elapsed{0},_active{false},_index{0}
{
	_pos = data.pos;
	auto light=std::make_unique<SignalLight>(game,mode,*this);
	_mode.GetActorServer().Add(std::move(light));

	_cg = ImageServer::LoadGraph("resource/Gimmick/biggen.png");
}

void BigGenerator::Update() {

	++_elapsed;
	if (_elapsed > _span) {
		++_index;
		_elapsed = 0;
	}
	if (_index >= _signal.size()) {
		_index = 0;
	}
	_activate = _signal[_index];

}

void BigGenerator::StandardRender(Vector2 window_pos, Vector2 camera_pos){
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg, 0);
}

void BigGenerator::Debug(Vector2 window_pos, Vector2 camera_pos){

	std::stringstream ss;
	ss << "activate"<<_activate;

	DrawString(_pos.x-camera_pos.x+window_pos.x,
		_pos.y-camera_pos.y + window_pos.y,
		ss.str().c_str(), GetColor(255, 255, 255));
}