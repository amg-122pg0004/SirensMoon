/*****************************************************************//**
 * \file   ModeServer.h
 * \brief  ���[�h�𓮓I�z��ɓ���ĊǗ�����N���X�ł��B
 * 
 * \author �y�������Y
 * \date   July 2022
 *********************************************************************/

#pragma once
#pragma once
#include <memory>
#include <vector>
#include "ModeBase.h"

class Game;

class ModeServer {
public:
	ModeServer(Game& game);
	~ModeServer();

	typedef std::vector<std::unique_ptr<ModeBase>>		TypeModes;	// ���[�h���X�g���`
	TypeModes& GetModes() { return _vModes; }

	void	Clear();
	void	Add(std::unique_ptr<ModeBase> mode);
	void	Del(ModeBase& mode);

	void Update();  // �X�V
	void Render();	// �`��
	void Debug();

protected:
	Game& _game;
	TypeModes _vModes;
	TypeModes _vPendingModes;
	bool	_updating;

	void	DeleteModes();
	void	AddPendingModes();


};
