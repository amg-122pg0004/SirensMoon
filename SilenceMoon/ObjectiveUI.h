#pragma once
#include "UIBase.h"
class SplitWindow;
class ObjectiveUI :public UIBase {

public:
	ObjectiveUI(Game&,ModeBase&, SplitWindow& window, Vector2,Vector2);
	Type GetType() { return Type::ObjectiveUI; }
	virtual void Update()override;
	void Render()override;
	enum class Message {
		GoServer,
		SerchEnemy,
		BossCanon,
		BossMissile1,
		BossMissile2,
		BossHeadbutt1,
		BossHeadbutt2,
		BossGenerator1,
		BossGenerator2,
		BossServer,
		BossRideRailgun
	};
	void ChangeMessage(Message next,int cg);
	void ChangeWarning(int no);
	void ReleaseWarning();

protected:
	int _cgOrange, _cgGreen,_cgRed1,_cgRed2;
	std::string _preMessage;
	std::string _message;
	std::string _nextMessage;
	int _preCG;
	int _nextCG;
	Vector2 _startPos;
	int _font;
	std::unordered_map <Message, std::string> _messageList = {
		{Message::GoServer,"サーバーへ向かう\nサーバーは黄色い点で\nミニマップに表示されている"},
		{Message::SerchEnemy,"重要宇宙人を特定し捕獲せよ"},
		{Message::BossCanon,"ミニマップから射線を読み取り回避せよ"},
		{Message::BossGenerator1,"正しい順番で発電機を起動せよ"},
		{Message::BossGenerator2,"発電機を起動する順番を\nサーバーから読み取れ"},
		{Message::BossHeadbutt1,"消えた敵の攻撃を下げ\n隙をついて攻撃せよ"},
		{Message::BossHeadbutt2,"消えた敵の位置をマップから探れ"},
		{Message::BossMissile1,"ミサイルを撃ち落とせ"},
		{Message::BossMissile2,"ミサイルを回避せよ"},
		{Message::BossRideRailgun,"巨大レールガンに乗り込み\nミッションを完遂せよ"},
	};
};

class ObjectiveUI1 :public ObjectiveUI {

public:
	ObjectiveUI1(Game&, ModeBase&, SplitWindow& window, Vector2, Vector2);
	Type GetType() { return Type::ObjectiveUI; }
	virtual void Update()override;
private:

};

class ObjectiveUI2 :public ObjectiveUI {

public:
	ObjectiveUI2(Game&, ModeBase&, SplitWindow& window, Vector2, Vector2);
	Type GetType() { return Type::ObjectiveUI; }
	void Update()override;
private:
};
