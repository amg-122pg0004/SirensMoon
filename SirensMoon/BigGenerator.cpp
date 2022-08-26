#include "BigGenerator.h"
#include "SignalLight.h"
#include "ModeGame.h"
#include <sstream>

BigGenerator::BigGenerator(Game& game, ModeGame& mode, ObjectDataStructs::BigServerData data)
	:Gimmick(game,mode,data.ID),_span{20},_elapsed{0},_active{false},_index{0},_pattern{-1},_signal{false}
{
	_pos = data.pos;
	auto light=std::make_unique<SignalLight>(game,mode,*this);
	_mode.GetActorServer().Add(std::move(light));

	_cg = ImageServer::LoadGraph("resource/Gimmick/biggen.png");
	int X, Y;
	GetGraphSize(_cg,&X,&Y);
	_size = { static_cast<double>(X), static_cast<double>(Y) };
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

	UpdateCollsiion();
	if (CheckHitBullet()) {

	}

}

bool BigGenerator::CheckHitBullet() {
	for (auto&& actor : _mode.GetObjects()) {
		auto type = actor->GetType();
		if (type == Actor::Type::RedBullet || type == Actor::Type::GreenBullet) {
			if(Intersect(_collision, actor->GetCollision()) ){
				return true;
			}
		}
	}
	return false;
}

void BigGenerator::StandardRender(Vector2 window_pos, Vector2 camera_pos){
	DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x)
		, static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg, 0);
}

void BigGenerator::Debug(Vector2 window_pos, Vector2 camera_pos){

	std::stringstream ss;
	ss << "activate"<<_activate;

	DrawString(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
		static_cast<int>(_pos.y-camera_pos.y + window_pos.y),
		ss.str().c_str(), GetColor(255, 255, 255));
}

void BigGenerator::UpdateCollsiion(){
	_collision.min = _pos;
	_collision.max = _pos + _size;
}

void BigGenerator::SetPattern(int pattern, std::vector<bool> signal){
	_pattern = pattern;
	_signal = signal;
}