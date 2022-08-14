#include "PlayerA.h"
#include "RedBullet.h"
#include "GreenBullet.h"
#include "ProjectionLight.h"
#include "ModeGame.h"

PlayerA::PlayerA(Game& game, ModeGame& base, int playernum) :Player(game, base, playernum),_setGreenBullet{false}
{
	Load();
}

void PlayerA::Load(){
	std::vector<int> handle;
	handle.resize(81);

	ImageServer::LoadDivGraph("resource/Player/PlayerA/Wait/back.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Wait/front.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Wait/left.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Wait/right.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Wait, PlayerDirection::Right}] = handle;

	ImageServer::LoadDivGraph("resource/Player/PlayerA/Walk/back.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Walk/front.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Walk/left.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Walk/right.png", 81, 10, 9, 150, 150, handle.data());
	_cg[{PlayerState::Walk, PlayerDirection::Right}] = handle;
	handle.resize(60);
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/back.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/front.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/left.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Run/right.png", 60, 10, 6, 150, 150, handle.data());
	_cg[{PlayerState::Run, PlayerDirection::Right}] = handle;

	handle.resize(16);
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Set/back.png", 16, 8, 2, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Set/front.png", 16, 8, 2, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Set/left.png", 16, 8, 2, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Set/right.png", 16, 8, 2, 150, 150, handle.data());
	_cg[{PlayerState::Set, PlayerDirection::Right}] = handle;

	handle.resize(41);
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Shoot/back.png", 41, 10, 5, 150, 150, handle.data());
	_cg[{PlayerState::Shoot, PlayerDirection::Up}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Shoot/front.png", 41, 10, 5, 150, 150, handle.data());
	_cg[{PlayerState::Shoot, PlayerDirection::Down}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Shoot/left.png", 41, 10, 5, 150, 150, handle.data());
	_cg[{PlayerState::Shoot, PlayerDirection::Left}] = handle;
	ImageServer::LoadDivGraph("resource/Player/PlayerA/Shoot/right.png", 41, 10, 5, 150, 150, handle.data());
	_cg[{PlayerState::Shoot, PlayerDirection::Right}] = handle;
}

void PlayerA::Action(){
	if (_inputManager->CheckInput("BULLET1", 't', _playerNum)&&_charge==0 ) {
		_setGreenBullet = true;
		PlaySoundMem(SoundServer::Find("PlayerOpenMap"), DX_PLAYTYPE_BACK);
	}
	if (_inputManager->CheckInput("BULLET2", 't', _playerNum) && _charge == 0) {
		_setGreenBullet = false;
		PlaySoundMem(SoundServer::Find("PlayerOpenMap"), DX_PLAYTYPE_BACK);
	}

	--_cooldown;
	if (_cooldown > 0) {
		_state = PlayerState::Shoot;

		std::vector<int> cg = _cg[{_state, _direction}];
		if (_animNo >= cg.size()-1) {
			_state = PlayerState::Wait;
		}
	}
	if (_cooldown < 0) {
		_cooldown = 0;
		
	}

	if (_inputManager->CheckInput("ACTION", 'r', _playerNum) && _charge >= 120) {
		_lastDir.Normalize();
		if (_bullet > 0) {
			if (_setGreenBullet) {
				auto bullet = std::make_unique<GreenBullet>(_game, _mode, _pos, _lastDir);
				_mode.GetActorServer().Add(std::move(bullet));
			}
			else {
				auto bullet = std::make_unique<RedBullet>(_game, _mode, _pos, _lastDir);
				_mode.GetActorServer().Add(std::move(bullet));
			}


			PlaySoundMem(SoundServer::Find("PlayerShoot"), DX_PLAYTYPE_BACK);
			_cooldown = 180;
			_movable = false;
			_state = PlayerState::Shoot;
			_animNo = 0;
			--_bullet;

			if (_bullet == 0) {
				_mode.GameOver();
			}
		}

	}

	if (_inputManager->CheckInput("ACTION", 'h', _playerNum) && _cooldown == 0) {
		_movable = false;
		_state = PlayerState::Set;
		if (_charge == 0) {
			auto gunlight = std::make_unique<ProjectionLight>(_game, _mode, *this);
			_mode.GetActorServer().Add(std::move(gunlight));
			_animNo = 0;
		}

		++_charge;
		if (_charge == 1) {
			PlaySoundMem(SoundServer::Find("PlayerAim"), DX_PLAYTYPE_BACK);
		}
		if (_charge == 12) {
			PlaySoundMem(SoundServer::Find("PlayerCharge"), DX_PLAYTYPE_BACK);
		}
		if (_charge == 105) {
			PlaySoundMem(SoundServer::Find("PlayerChargeMAX"), DX_PLAYTYPE_BACK);
		}

	}
	else {
		if (_cooldown < 132) {
			_movable = true;
		}
		_charge = 0;
		StopSoundMem(SoundServer::Find("PlayerCharge"));
	}
}
