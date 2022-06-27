#include <DxLib.h>
#include "ActorServer.h"
#include "Actor.h"

ActorServer::ActorServer(Game& game) :
	_game{ game },
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


void	ActorServer::Del(Actor& actor) {
	actor.Dead();
}


void	ObjectServer::DeleteObjects() {
	// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
	for (auto ite = _vObjects.begin(); ite != _vObjects.end(); ) {
		if ((*ite)->IsDead()) {
			ite = _vObjects.erase(ite);		// これでobjectそのものも削除される
		}
		else {
			++ite;
		}
	}

	void	ObjectServer::Update() {
		_updating = true;
		for (auto&& object : _vObjects) {
			object->Update();
		}
		_updating = false;
		AddPendingObjects();
		DeleteObjects();	// 削除予約されたオブジェクトを削除する
	}

	void	ObjectServer::Render() {
		for (auto&& object : _vObjects) {
			object->Render();
		}
	}