/*****************************************************************//**
 * \file   ModeServer.cpp
 * \brief  モードを動的配列に入れて管理するクラスです。
 * 
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#include "DxLib.h"
#include "ModeBase.h"
#include "ModeServer.h"
#include <algorithm>

class Game;

ModeServer::ModeServer(Game& game)
	: _game(game), _updating(false)
{
}

ModeServer::~ModeServer()
{
	Clear();
}

void ModeServer::Clear()
{
	if (_updating) {
		for (auto&& mode : _vModes) {
			mode->Dead();
		}
	}
	else {
		_vModes.clear();
	}
}

void	ModeServer::Add(std::unique_ptr<ModeBase> mode) {
	
	if (_updating) {
		_vPendingModes.push_back(std::move(mode));
	}
	else {
		_vModes.push_back(std::move(mode));
	}
}

void	ModeServer::AddPendingModes() {
	// _vPendingModes -> _vModes に追加
	_vModes.insert(
		_vModes.end(),
		make_move_iterator(_vPendingModes.begin()),
		make_move_iterator(_vPendingModes.end())
	);
	// _vPendingModes をクリア
	_vPendingModes.clear();
}


void	ModeServer::Del(ModeBase& mode) {
	mode.Dead();
}


void	ModeServer::DeleteModes() {
	// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
	for (auto ite = _vModes.begin(); ite != _vModes.end(); ) {
		if ((*ite)->IsDead()) {
			ite = _vModes.erase(ite);		// これでobjectそのものも削除される
		}
		else {
			++ite;
		}
	}

	// 上記は、以下のような書き方もできる。
	/*
	_vModes.erase(
		std::remove_if(
			_vModes.begin(),
			_vModes.end(),
			[](auto&& object) {
				return object->IsDead();
			}
		),
		_vModes.end()
	);
	*/
}

bool CompRenderPriority(const std::unique_ptr<ModeBase>& a, const std::unique_ptr<ModeBase>& b)
{
	return a->GetRenderPriority() < b->GetRenderPriority();
}

// 更新
void ModeServer::Update() {
	_updating = true;
	for (auto&& mode : _vModes) {
		mode->Update();
	}
	_updating = false;
	AddPendingModes();
	DeleteModes();	// 削除予約されたオブジェクトを削除する
	std::sort(_vModes.begin(), _vModes.end(), CompRenderPriority);
}

// 描画
void ModeServer::Render() {
	for (auto&& mode : _vModes) {
		mode->Render();
	}
}


void ModeServer::Debug() {
	for (auto&& mode : _vModes) {
		mode->Debug();
	}
}