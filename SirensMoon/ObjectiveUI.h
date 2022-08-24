#pragma once
#include "UIBase.h"

class ObjectiveUI :public UIBase {

public:
	ObjectiveUI(Game&,ModeBase&,Vector2,Vector2);
	Type GetType() { return Type::ObjectiveUI; }
	virtual void Update()override;
	void Render()override;
	void ChangeMessage(std::string next);

protected:
	int _cg2, _cg3;
	std::string _message;
	std::string _nextMessage;
	Vector2 _startPos;
	int _font;
};

class ObjectiveUI1 :public ObjectiveUI {

public:
	ObjectiveUI1(Game&, ModeBase&, Vector2, Vector2);
	Type GetType() { return Type::ObjectiveUI; }
	virtual void Update()override;
private:

};

class ObjectiveUI2 :public ObjectiveUI {

public:
	ObjectiveUI2(Game&, ModeBase&, Vector2, Vector2);
	Type GetType() { return Type::ObjectiveUI; }
	void Update()override;
private:
};
