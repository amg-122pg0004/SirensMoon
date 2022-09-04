/*****************************************************************//**
 * \file   UIBase.h
 * \brief  UIの親クラスです。
 *
 * \author 土居将太郎
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "Math.h"
#include "ImageServer.h"

class Game;
class ModeBase;

class UIBase {
public:
	UIBase(Game&, ModeBase&, Vector2 pos, Vector2 size);
	~UIBase();
	virtual void Update();
	virtual void Render();
	enum class Type {
		MiniMap,
		ServerMachine,
		Pause,
		HP,
		Ammo,
		BulletType,
		GameOver,
		DamageCut,
		FoundUI,
		ButtonIcon,
		ObjectiveUI,
		MessageWindow,
		BigServerUI,
		AimUI,
		FinishCut
	};
	virtual Type GetType() = 0;
	virtual void DamageEvent();
	virtual void TargetKillEvent();
	void SetVisibillity(bool flag) { _visible = flag; }
protected:
	Vector2 _pos;
	Vector2 _size;
	Game& _game;
	ModeBase& _mode;
	bool _visible;
	int _cg;
};