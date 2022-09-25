#include "Briefing.h"
#include "ModeGame.h"
#include "UIServer.h"
#include "Screen_Fade.h"

class SplitWindow;

Briefing::Briefing(Game& game, ModeBase& mode, SplitWindow& window, Vector2 pos, Vector2 size)
	:UIBase{ game,mode,window,pos,size }, _slideTime{ 200 }, _slideNo{ 0 }, _nextslideNo{ 0 }
{
	_inputManager = _game.GetInputManager();
	_cg.push_back(ImageServer::LoadGraph("resource/UI/Briefing/1.png"));
	_cg.push_back(ImageServer::LoadGraph("resource/UI/Briefing/2.png"));
	_cg.push_back(ImageServer::LoadGraph("resource/UI/Briefing/3.png"));
	_cg.push_back(ImageServer::LoadGraph("resource/UI/Briefing/4.png"));
	dynamic_cast<ModeGame&>(_mode).SetPauseGame(true);
	_visible = true;
	_UIPriority = 12;
	_slideTimeMax = _slideTime;
	auto fade = std::make_unique<Screen_Fade>(_game, _mode, _window, _pos, _size);
	fade->SetEffect(0, 20, GetColor(0, 0, 0), true);
	_window.GetUIServer2().Add(std::move(fade));
	auto fade2 = std::make_unique<Screen_Fade>(_game, _mode, _window, _pos, _size);
	fade2->SetEffect(180, 22, GetColor(0, 0, 0),false);
	_window.GetUIServer2().Add(std::move(fade2));
	PlaySoundFile("resource/BGM/Briefing.mp3", DX_PLAYTYPE_BACK);
}
Briefing::~Briefing() {

}
void Briefing::Update() {
	_slideNo = _nextslideNo;
	--_slideTime;
	if (_slideTime < 0) {
		_slideTime = _slideTimeMax;
		++_nextslideNo;
		if (_nextslideNo >= _cg.size()) {
			_slideNo = 0;
			_visible = false;
			dynamic_cast<ModeGame&>(_mode).SetPauseGame(false);
			StopSoundFile();
			static_cast<ModeGame&>(_mode).PlayBGM();
			_dead = true;
			return;
		}
		auto fade = std::make_unique<Screen_Fade>(_game, _mode,_window, _pos, _size);
		fade->SetEffect(0, 20, GetColor(0, 0, 0), true);
		_window.GetUIServer2().Add(std::move(fade));
		auto fade2 = std::make_unique<Screen_Fade>(_game, _mode, _window, _pos, _size);
		fade2->SetEffect(180, 22, GetColor(0, 0, 0), false);
		_window.GetUIServer2().Add(std::move(fade2));

	}
}

void Briefing::Render() {
	if (_visible) {
		SetDrawArea(static_cast<int>(_pos.x), static_cast<int>(_pos.y)
			, static_cast<int>(_pos.x + splitscreen_W), static_cast<int>(screen_H));
		DrawBox(0, 0, screen_W, screen_H, GetColor(0, 0, 0), 1);
		DrawExtendGraph(static_cast<int>(_pos.x), static_cast<int>(_pos.y)
			, static_cast<int>(_pos.x + splitscreen_W), static_cast<int>(_pos.y + screen_H), _cg[_slideNo], 1);
		SetDrawArea(0, 0,screen_W,screen_H);
	}
}