/*****************************************************************//**
 * \file   UIBase.h
 * \brief  UI�̐e�N���X�ł��B
 *
 * \author �y�������Y
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

	/*�v���C���[���_���[�W���󂯂����ɌĂ΂��֐�*/
	virtual void DamageEvent();
	/*�d�v�F���l���X�|�[���������ɌĂ΂��֐�*/
	virtual void TargetSpawnEvent();
	/*�d�v�F���l���|���ꂽ���ɌĂ΂��֐�*/
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