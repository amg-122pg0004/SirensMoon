#pragma once
#include "UIBase.h"
#include "Math.h"
#include "InputManager.h"
#include "EnemyGenerator.h"
#include <memory>

class ServerMachine;
class Game;
class ModeBase;

class ServerMachineUI :public UIBase{
	public:
		ServerMachineUI(Game&,ModeBase&,Vector2,Vector2,ServerMachine&,EnemyGenerator::EnemyPattern patern);
		Type GetType() { return Type::ServerMachine; }
		void Update();
		void Render();
		bool GetVisibility() { return _visible; }
	private:
		/*•\¦ó‘Ô‚©‚ğ¦‚·ƒtƒ‰ƒO*/
		bool _visible;
		ServerMachine& _owner;
		std::shared_ptr<InputManager> _inputManager;

		int _cg_top, _cg_top2;
		int _cg_mid;
		int _cg_bot;
};