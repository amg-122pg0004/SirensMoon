#include "Player.h"
#include "ImageServer.h"
#include "MapChip.h"
#include <string>
#include <sstream>

Player::Player(Game& game,int playernum)
	:Actor{ game }, _speed{ 5 }, _playerNum{playernum}
	, _dirX{ 0 }, _dirY{ 0 }
{
	 _inputManager = _game.GetInputManager();
	 
	 _cg_up = ImageServer::LoadGraph("resource/player/up.png");
	 _cg_side = ImageServer::LoadGraph("resource/player/side.png");
	 _cg_down = ImageServer::LoadGraph("resource/player/down.png");

	 _pos = { 200,200 };
	 _stage = 1;
}

void Player::Update() {

	int fix_x,fix_y = 0;

	_dirY = 0;
	if (_inputManager->CheckInput("UP", 'h', _playerNum)) {
		--_dirY;
		_state = State::UP;
	}
	if (_inputManager->CheckInput("DOWN", 'h', _playerNum)) {
		++_dirY;
		_state = State::DOWN;
	}

	_dirX = 0;
	if (_inputManager->CheckInput("LEFT", 'h', _playerNum)) {
		--_dirX;
		_state = State::LEFT;
	}
	if (_inputManager->CheckInput("RIGHT", 'h', _playerNum)) {
		++_dirX;
		_state = State::RIGHT;
	}

	_pos.x = _pos.x + _dirX * _speed;
	fix_x = _game.GetMapChips()->IsHit(_stage-1,*this, _dirX);
	_pos.x += fix_x * _speed;

	_pos.y = _pos.y + _dirY * _speed;
	fix_y = _game.GetMapChips()->IsHit(_stage-1,*this, _dirY);
	_pos.y += fix_y * _speed;


	if (_pos.x > 750 && _dirX>0|| 
		_pos.x < 15 && _dirX <0) {
		int transition = _game.GetMapChips()->CheckTransitionChip(_stage, *this);
		if (transition!= 0) {
			_pos.x -= _game.GetSplitWindow()[_playerNum]->GetWindowSize_W()*_dirX;
			_game.GetSplitWindow()[_playerNum]->ChangeRenderStage(transition);
			_stage=_stage+transition;
		}
	}

	if (_pos.y > 850 && _dirY >0 ||
		_pos.y < 15 && _dirY < 0) {
		int transition = _game.GetMapChips()->CheckTransitionChip(_stage, *this);
		if (transition != 0) {
			_pos.y -= _game.GetSplitWindow()[_playerNum]->GetWindowSize_H()*_dirY;
			_game.GetSplitWindow()[_playerNum]->ChangeRenderStage(transition);
			_stage = _stage + transition;
		}
	}

	/*
	if (_pos.x > 750&&_dirX>0) {
		_pos.x += _game.GetSplitWindow()[_playerNum]->GetWindowSize_W();
		_game.GetSplitWindow()[_playerNum]->ChangeRenderStage(1);
		--_stage;
	}

	if (_pos.x < 15&&_dirX<0) {
		_pos.x += _game.GetSplitWindow()[_playerNum]->GetWindowSize_W();
		_game.GetSplitWindow()[_playerNum]->ChangeRenderStage(-1);
		--_stage;
	}

	if (_pos.y > 880) {
		_pos.y -= _game.GetSplitWindow()[_playerNum]->GetWindowSize_H();
		_game.GetSplitWindow()[_playerNum]->ChangeRenderStage(2);
		_stage+=2;
	}

	if (_pos.y <15) {
		_pos.y += _game.GetSplitWindow()[_playerNum]->GetWindowSize_H();
		_game.GetSplitWindow()[_playerNum]->ChangeRenderStage(-2);
		_stage -= 2;
	}
	*/


	/*
	_collision.min = _pos;
	_collision.max = { _pos.x + 48,_pos.y + 48 };
	*/
}

void Player::Render(int stageNum,Vector2 window_pos,Vector2 camera_pos){
	std::stringstream ss;

	ss << (_pos.x + _size.x / 2) / _game.GetMapChips()->GetChipSize_W()<<"\n";
	ss << (_pos.y + _size.y / 2) / _game.GetMapChips()->GetChipSize_H() << "\n";

	DrawString(500+ _playerNum*800, 100, ss.str().c_str(), GetColor(0, 0, 0));
	if(_stage==stageNum){
		switch (_state) {
		case State::UP:
			DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_up, 0);
			break;
		case State::DOWN:
			DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_down, 0);
			break;
		case State::LEFT:
			DrawTurnGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_side, 0);
			break;
		case State::RIGHT:
			DrawGraph(static_cast<int>(_pos.x + window_pos.x - camera_pos.x),
				static_cast<int>(_pos.y + window_pos.y - camera_pos.y), _cg_side, 0);
			break;
		}
	}
}
