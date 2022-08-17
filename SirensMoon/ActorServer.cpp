/*****************************************************************//**
 * \file   ActorServer.h
 * \brief  全てのアクターを動的配列_typeActorsに入れて管理します。
 *
 * \author 土居将太郎
 * \date   June 2022
 *********************************************************************/

#include "ActorServer.h"
#include <algorithm>

ActorServer::ActorServer(ModeBase& mode) :
	_mode{mode}, _updating{ false }
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
	std::reverse(begin(_pendingTypeActors),end(_pendingTypeActors));
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

bool CompRenderPriority(const std::unique_ptr<Actor>& a, const std::unique_ptr<Actor>& b)
{
	return a->GetRenderPriority() < b->GetRenderPriority();
}

void	ActorServer::Update() {
		_updating = true;



		for (auto&& object : _typeActors) {
			object->Update();
		}
		for (auto&& object : _typeActors) {
			object->CheckDeadOwner();
		}
		_updating = false;
		AddPendingActors();
		DeleteObjects();	// 削除予約されたオブジェクトを削除する

		std::sort(_typeActors.begin(), _typeActors.end(), CompRenderPriority);
	}

	void	ActorServer::StandardRender(int stageNum,Vector2 window_pos, Vector2 camera_pos) {
		for (auto&& object : _typeActors) {
			object->StandardRender(stageNum,window_pos,camera_pos);
		}
	}

	void	ActorServer::ReconRender(int stageNum, Vector2 window_pos, Vector2 camera_pos) {
		for (auto&& object : _typeActors) {
			object->ReconRender(stageNum, window_pos, camera_pos);
		}
	}


void ActorServer::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	for (auto&& object : _typeActors) {
		object->Debug(stageNum, window_pos, camera_pos);
	}
}
