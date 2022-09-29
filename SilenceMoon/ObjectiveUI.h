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
		{Message::GoServer,"�T�[�o�[�֌�����\n�T�[�o�[�͉��F���_��\n�~�j�}�b�v�ɕ\������Ă���"},
		{Message::SerchEnemy,"�d�v�F���l����肵�ߊl����"},
		{Message::BossCanon,"�~�j�}�b�v����ː���ǂݎ��������"},
		{Message::BossGenerator1,"���������ԂŔ��d�@���N������"},
		{Message::BossGenerator2,"���d�@���N�����鏇�Ԃ�\n�T�[�o�[����ǂݎ��"},
		{Message::BossHeadbutt1,"�������G�̍U��������\n�������čU������"},
		{Message::BossHeadbutt2,"�������G�̈ʒu���}�b�v����T��"},
		{Message::BossMissile1,"�~�T�C�����������Ƃ�"},
		{Message::BossMissile2,"�~�T�C�����������"},
		{Message::BossRideRailgun,"���僌�[���K���ɏ�荞��\n�~�b�V��������������"},
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
