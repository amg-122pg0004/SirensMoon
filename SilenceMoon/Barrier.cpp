#include "Barrier.h"
#include "Game.h"
#include <sstream>

Barrier::Barrier(Game& game, ModeGame& mode, BarrierData data)
	:Gimmick(game,mode,data.ID),_animSpeed{50.0}, _alpha{0}
{
	_pos = data.pos;
	_size = { 30,30 };
	_collision.min = _pos;
	_collision.max = _pos + _size;
	_renderPriority = static_cast<int>(_pos.y+_size.y);
}

void Barrier::Update() {
	_alpha = static_cast<int>((sin(static_cast<double>(_game.GetFrameCount()) / _animSpeed) + 1.0) / 2.0 * 255);
}

void Barrier::StandardRender(Vector2 window_pos, Vector2 camera_pos)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255-_alpha-30);
	DrawGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
		_cg.first, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha-30);
	DrawGraph(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y),
		_cg.second, 1);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
void Barrier::Debug(Vector2 window_pos, Vector2 camera_pos) {
	std::stringstream ss;
	auto test=static_cast<double>(_game.GetFrameCount() / _animSpeed);
	ss << "alpha " << _alpha<< "“K“–" <<test;
	DrawString(static_cast<int>(_pos.x - camera_pos.x + window_pos.x),
		static_cast<int>(_pos.y - camera_pos.y + window_pos.y), 
		ss.str().c_str(),
		GetColor(255,255,255));
}

BarrirA::BarrirA(Game& game, ModeGame& mode, BarrierData data)
	:Barrier(game,mode,data) {
	_cg.first = ImageServer::LoadGraph("resource/Gimmick/Barrier/A1.png");
	_cg.second= ImageServer::LoadGraph("resource/Gimmick/Barrier/A2.png");
}

BarrirB::BarrirB(Game& game, ModeGame& mode, BarrierData data)
	:Barrier(game, mode, data) {
	_cg.first = ImageServer::LoadGraph("resource/Gimmick/Barrier/B1.png");
	_cg.second = ImageServer::LoadGraph("resource/Gimmick/Barrier/B2.png");
}