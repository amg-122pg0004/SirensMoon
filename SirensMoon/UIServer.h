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

	/** Actor���y���f�B���O�ɒǉ����� */
	void Add(std::unique_ptr<UIBase> actor);
	void Delete(UIBase& actor);


	void Update(); //<�e�A�N�^�[��Update���Ăяo��
	void Render(); //<�e�A�N�^�[��Render���Ăяo��

	void Debug();


private:
	std::vector<std::unique_ptr<UIBase>> _typeUIBase;
	std::vector<std::unique_ptr<UIBase>> _pendingTypeUIBase;

	/*Actors�͈̓��[�v������Ă��Ȃ������m�F���邽�߂̃t���O*/
	bool _updating;

	/*�y���f�B���O��UI���Q�[�����ɒǉ�*/
	void AddPendingActors();
	void DeleteObjects();
	ModeBase& _mode;
};
