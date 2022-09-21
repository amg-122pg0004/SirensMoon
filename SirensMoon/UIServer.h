#pragma once

#include <memory>
#include <vector>
#include "Math.h"
#include "UIBase.h"

class ModeBase;
class SplitWindow;


class UIServer {

public:
	UIServer(ModeBase&);
	std::vector<std::unique_ptr<UIBase>>& GetObjects() { return _typeUIBase; }

	void Clear();

	/** Actorをペンディングに追加する */
	void Add(std::unique_ptr<UIBase> actor);
	void Delete(UIBase& actor);


	void Update(); //<各アクターのUpdateを呼び出す
	void Render(); //<各アクターのRenderを呼び出す

	void Debug();


private:
	std::vector<std::unique_ptr<UIBase>> _typeUIBase;
	std::vector<std::unique_ptr<UIBase>> _pendingTypeUIBase;

	/*Actors範囲ループが回っていない事を確認するためのフラグ*/
	bool _updating;

	/*ペンディングのUIをゲーム内に追加*/
	void AddPendingActors();
	void DeleteObjects();
	ModeBase& _mode;
};
