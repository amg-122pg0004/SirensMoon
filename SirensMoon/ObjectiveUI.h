#pragma once
#include "UIBase.h"
class SplitWindow;
class ObjectiveUI :public UIBase {

public:
	ObjectiveUI(Game&,ModeBase&, SplitWindow& window, Vector2,Vector2);
	Type GetType() { return Type::ObjectiveUI; }
	virtual void Update()override;
	void Render()override;
	void ChangeMessage(std::string next,int cg);
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
