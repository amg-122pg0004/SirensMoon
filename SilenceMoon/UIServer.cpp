#include "UIServer.h"
#include "SplitWindow.h"
#include <algorithm>

UIServer::UIServer(ModeBase& mode) :
	_mode{ mode }, _updating{ false }
{
	Clear();
}

void UIServer::Clear() {
	_typeUIBase.clear();
}

void UIServer::Add(std::unique_ptr<UIBase> ui) {
	if (_updating) {
		_pendingTypeUIBase.push_back(std::move(ui));
	}
	else {
		_typeUIBase.push_back(std::move(ui));
	}
}

void	UIServer::AddPendingActors() {
	std::reverse(begin(_pendingTypeUIBase), end(_pendingTypeUIBase));
	_typeUIBase.insert(
		_typeUIBase.end(),
		make_move_iterator(_pendingTypeUIBase.begin()),
		make_move_iterator(_pendingTypeUIBase.end())
	);

	_pendingTypeUIBase.clear();
}


void UIServer::Delete(UIBase& ui) {
	ui.Dead();
}


void	UIServer::DeleteObjects() {
	// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
	for (auto ite = _typeUIBase.begin(); ite != _typeUIBase.end(); ) {
		if ((*ite)->IsDead()) {
			ite = _typeUIBase.erase(ite);		// これでobjectそのものも削除される
		}
		else {
			++ite;
		}
	}
}

bool CompRenderPriority(const std::unique_ptr<UIBase>& a, const std::unique_ptr<UIBase>& b)
{
	return a->GetUIPriority() < b->GetUIPriority();
}

void	UIServer::Update() {
	_updating = true;



	for (auto&& ui : _typeUIBase) {
		ui->Update();
	}
	_updating = false;
	AddPendingActors();
	DeleteObjects();	// 削除予約されたオブジェクトを削除する

	std::sort(_typeUIBase.begin(), _typeUIBase.end(), CompRenderPriority);
}

void UIServer::Render() {
	for (auto&& ui : _typeUIBase) {
		ui->Render();
	}
}


void UIServer::Debug() {
	for (auto&& ui : _typeUIBase) {
		ui->Debug();
	}
}
