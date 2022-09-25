/*****************************************************************//**
 * \file   ModeBase.h
 * \brief  ���[�h�̐e�N���X�ł��B
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "ActorServer.h"
class Game;

class ModeBase {
public:
	ModeBase(Game& game);
	virtual ~ModeBase();

	virtual void Update();  // �X�V
	virtual void Render();	// �`��
	virtual void Debug(); //�f�o�b�O

	virtual ActorServer& GetActorServer() { return _actorServer; }
	 virtual ActorServer::TypeActors& GetObjects() { return _actorServer.GetObjects(); }

	virtual bool IsDead() { return _dead; }
	virtual void Dead() { _dead = true; }
	int GetRenderPriority() { return _renderPriority; }

	virtual void NextMode();

	void CallPlayStage1();
	void CallPlayStage2();
	void CallPlayStage3();

protected:
	Game& _game;
	bool	_dead;
	//std::unique_ptr<ActorServer> _actorServer;
	ActorServer _actorServer;

	int _renderPriority;

	bool _makedNextMode;
	int _delayNextMode;
};