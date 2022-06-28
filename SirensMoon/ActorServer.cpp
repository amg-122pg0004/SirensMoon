/*****************************************************************//**
 * \file   ActorServer.h
 * \brief  全てのアクターを動的配列_typeActorsに入れて管理します。
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "ActorServer.h"

ActorServer::ActorServer() :
	_updating{ false }
{
	Clear();
}

void ActorServer::Clear() {
	_typeActors.clear();
}

void	ActorServer::Add(std::unique_ptr<Actor> actor) {
	if (_updating) {
		_pendingTypeActors.push_back(std::move(actor));
	}
	else {
		_typeActors.push_back(std::move(actor));
	}
}

void	ActorServer::AddPendingActors() {
	
	_typeActors.insert(
		_typeActors.end(),
		make_move_iterator(_pendingTypeActors.begin()),
		make_move_iterator(_pendingTypeActors.end())
	);
	
	_pendingTypeActors.clear();
}


void	ActorServer::Delete(Actor& actor) {
	actor.Dead();
}


void	ActorServer::DeleteObjects() {
	// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
	for (auto ite = _typeActors.begin(); ite != _typeActors.end(); ) {
		if ((*ite)->IsDead()) {
			ite = _typeActors.erase(ite);		// これでobjectそのものも削除される
		}
		else {
			++ite;
		}
	}
}

void	ActorServer::Update() {
		_updating = true;
		for (auto&& object : _typeActors) {
			object->Update();
		}
		_updating = false;
		AddPendingActors();
		DeleteObjects();	// 削除予約されたオブジェクトを削除する
	}

	void	ActorServer::Render() {
		for (auto&& object : _typeActors) {
			object->Render();
		}
	}
