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
class SplitWindow;

class UIBase {
public:
	UIBase(Game&, ModeBase&, SplitWindow&, Vector2 pos, Vector2 size);
	~UIBase();
	virtual void Update();
	virtual void Render();
	virtual void Debug();
	enum class Type {
		MiniMap,
		ServerMachine,
		Pause,
		PauseInfoA,
		PauseInfoB,
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
		FinishCut,
		SkipUI,
		RideInfo,
		ScreenEffect,
		Briefing,
		SerchInfo,
		BossGunFireUI
	};
	virtual Type GetType() = 0;
	int GetUIPriority(){return _UIPriority;}

	/*プレイヤーがダメージを受けた時に呼ばれる関数*/
	virtual void DamageEvent();
	/*重要宇宙人がスポーンした時に呼ばれる関数*/
	virtual void TargetSpawnEvent();
	/*重要宇宙人が倒された時に呼ばれる関数*/
	virtual void TargetKillEvent();

	virtual void SetVisibillity(bool flag) { _visible = flag; }
	virtual bool IsDead() { return _dead; }
	virtual void Dead() { _dead = true; }
protected:
	bool _dead;
	Vector2 _pos;
	Vector2 _size;
	Game& _game;
	ModeBase& _mode;
	SplitWindow& _window;
	bool _visible;
	int _cg;
	int _UIPriority;
};