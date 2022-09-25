#pragma once
#include "UIBase.h"
#include "Math.h"
#include "InputManager.h"
#include "EnemyGenerator.h"
#include "CharaCodeConvert.h"
#include <memory>
class SplitWindow;
class ServerMachine;
class Game;
class ModeBase;

class ServerMachineUI :public UIBase{
	public:
		ServerMachineUI(Game&,ModeBase&, SplitWindow& window, Vector2,Vector2);
		Type GetType() { return Type::ServerMachine; }
		void Update();
		void Render();
		bool GetVisibility() { return _visible; }

		void SetCGHandle(EnemyGenerator::EnemyPattern pattern);

	private:
		void LoadMessage(EnemyGenerator::EnemyPattern pattern);
		/*•\¦ó‘Ô‚©‚ğ¦‚·ƒtƒ‰ƒO*/
		bool _visible;
		std::shared_ptr<InputManager> _inputManager;
		int _alpha;
		int _animNo;
		int _font;
		std::vector<std::string> _message;
		std::vector<int> _cg_top, _cg_top2;
		std::vector<int> _cg_mid;
		std::vector<int> _cg_bot;
};