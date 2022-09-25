/*****************************************************************//**
 * \file   ActorServer.h
 * \brief  �S�ẴA�N�^�[�𓮓I�z��_typeActors�ɓ���ĊǗ����܂��B
 *
 * \author �y�������Y
 * \date   June 2022
 *********************************************************************/

#include "ActorServer.h"
#include "SplitWindow.h"
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
	// �R���e�i���C�e���[�^�ŉ�( erase���C�e���[�^��v�����Ă��邽�� )
	for (auto ite = _typeActors.begin(); ite != _typeActors.end(); ) {
		if ((*ite)->IsDead()) {
			ite = _typeActors.erase(ite);		// �����object���̂��̂��폜�����
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



		for (auto&& actor : _typeActors) {
			actor->Update();
		}
		for (auto&& actor : _typeActors) {
			actor->CheckDeadOwner();
		}
		_updating = false;
		AddPendingActors();
		DeleteObjects();	// �폜�\�񂳂ꂽ�I�u�W�F�N�g���폜����

		std::sort(_typeActors.begin(), _typeActors.end(), CompRenderPriority);
	}

	void ActorServer::StandardRender(Vector2 window_pos, Vector2 camera_pos, SplitWindow& split) {
		for (auto&& actor : _typeActors) {
			/*�e�t���O���Q�Ƃ��ē���̃^�C�v�̕`����X�L�b�v*/
			if (split.GetInvisiblePlayer()) {
				if (split.GetWindowNo() == 0) {
					if (actor->GetType() == Actor::Type::PlayerB) {
						continue;
					}
				}
				else {
					if (actor->GetType() == Actor::Type::PlayerA) {
						continue;
					}
				}
			}
			actor->StandardRender(window_pos,camera_pos);
		}
	}
	void ActorServer::BackRender(Vector2 window_pos, Vector2 camera_pos) {
		for (auto&& actor : _typeActors) {
			actor->BackRender(window_pos, camera_pos);
		}
	}


void ActorServer::Debug(int stageNum, Vector2 window_pos, Vector2 camera_pos){
	for (auto&& actor : _typeActors) {
		actor->Debug(window_pos, camera_pos);
	}
}
