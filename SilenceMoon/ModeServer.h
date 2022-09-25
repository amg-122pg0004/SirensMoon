/*****************************************************************//**
 * \file   ModeServer.h
 * \brief  モードを動的配列に入れて管理するクラスです。
 * 
 * \author 土居将太郎
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

	typedef std::vector<std::unique_ptr<ModeBase>>		TypeModes;	// モードリストを定義
	TypeModes& GetModes() { return _vModes; }

	void	Clear();
	void	Add(std::unique_ptr<ModeBase> mode);
	void	Del(ModeBase& mode);

	void Update();  // 更新
	void Render();	// 描画
	void Debug();

protected:
	Game& _game;
	TypeModes _vModes;
	TypeModes _vPendingModes;
	bool	_updating;

	void	DeleteModes();
	void	AddPendingModes();


};
