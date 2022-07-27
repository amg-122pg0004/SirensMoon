#pragma once
#include "UIBase.h"
#include "Math.h"
#include "InputManager.h"
#include <memory>

class ServerMachine;
class Game;
class ModeBase;

class ServerMachineUI :public UIBase{
	public:
		ServerMachineUI(Game&,ModeBase&,Vector2,Vector2,ServerMachine&);
		Type GetType() { return Type::ServerMachine; }
		void Update();
		void Render();
		bool GetVisibility() { return _visible; }
	private:
		/*•\¦ó‘Ô‚©‚ğ¦‚·ƒtƒ‰ƒO*/
		bool _visible;
		ServerMachine& _owner;
		std::shared_ptr<InputManager> _inputManager;

		std::vector<int> _cg_red1, _cg_red2, _cg_red3;
		std::vector<int> _cg_blue1, _cg_blue2, _cg_blue3;
		std::vector<int> _cg_green1, _cg_green2, _cg_green3;
};