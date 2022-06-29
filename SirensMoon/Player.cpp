#include "Player.h"
#include "ImageServer.h"
#include "MapChip.h"

Player::Player(Game& game,int playernum)
	:Actor{ game }, _speed{ 5 }, _playerNum{playernum}
	,_dirX{0},_dirY{0}
{
	 _inputManager = _game.GetInputManager();
	 
	 _cg_up = ImageServer::LoadGraph("resource/player/up.png");
	 _cg_side = ImageServer::LoadGraph("resource/player/side.png");
	 _cg_down = ImageServer::LoadGraph("resource/player/down.png");

	 _pos = { 50,50 };
}

void Player::Update() {

	_collision.min = _pos;
	_collision.max = { _pos.x + 48,_pos.y + 48 };


	if (_inputManager->CheckInput("UP", 'h', _playerNum)) {
		_dirY = -1;
		_state = State::UP;
	}
	else if (_inputManager->CheckInput("DOWN", 'h', _playerNum)) {
		_dirY = 1;
		_state = State::DOWN;
	}
	else {
		_dirY = 0;
	}

	if (_inputManager->CheckInput("LEFT", 'h', _playerNum)) {
		_dirX = -1;
		_state = State::LEFT;
	}
	else if (_inputManager->CheckInput("RIGHT", 'h', _playerNum)) {
		_dirX = 1;
		_state = State::RIGHT;
	}
	else {
		_dirX = 0;
	}

	_pos = { _pos.x + _dirX * _speed,_pos.y + _dirY * _speed };
	IsHitMapChip(_dirX, _dirY);
	
}

int Player::IsHitMapChip(int dirX, int dirY) {
	int x, y;
	for (y = static_cast<int>(_collision.min.y) / _game.GetMapChip()->GetChipSize_H();
		y < static_cast<int>(_collision.max.y)/ _game.GetMapChip()->GetChipSize_H(); y++) {
		for (x = static_cast<int>(_collision.min.x) / _game.GetMapChip()->GetChipSize_W();
			x < static_cast<int>(_collision.max.x) / _game.GetMapChip()->GetChipSize_W(); x++) {
			int chip_no = CheckHitMapChip(x, y);
			if (chip_no != 0)
			{	// このチップと当たった。
				// X,Yの移動方向を見て、その反対方向に補正する
				if (_dirX < 0)
				{	// 左に動いていたので、右に補正
					_pos.x = x * _game.GetMapChip()->GetChipSize_W() + _game.GetMapChip()->GetChipSize_W();// -(chara[i].hit_x);
				}
				if (_dirX > 0)
				{	// 右に動いていたので、左に補正
					_pos.x = x * _game.GetMapChip()->GetChipSize_W();// -(chara[i].hit_x + chara[i].hit_w);
				}
				if (_dirY > 0)
				{	// 下に動いていたので、上に補正
					_pos.y = y * _game.GetMapChip()->GetChipSize_H();// -(chara[i].hit_y + chara[i].hit_h);
				}
				if (_dirY < 0)
				{	// 上に動いていたので、下に補正
					_pos.y = y * _game.GetMapChip()->GetChipSize_H() + _game.GetMapChip()->GetChipSize_H();// -(chara[i].hit_y);
				}
				// 当たったので戻る
				return 1;
			}
		}
		return 0;
	}
}

int Player::CheckHitMapChip(int x, int y) {
	//int chip_no = _game.GetMapChip()->GetMapData();//[y * _game.GetMapChip()->GetChipSize_W()+x];
	return 0;
}

void Player::Render(Vector2 window_pos,Vector2 camera_pos){
	switch (_state) {
		case State::UP:
			DrawGraph(static_cast<int>(_pos.x+window_pos.x-camera_pos.x),
				static_cast<int>(_pos.y+window_pos.y-camera_pos.y), _cg_up, 0);
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
