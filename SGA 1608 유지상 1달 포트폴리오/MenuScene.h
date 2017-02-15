#pragma once

#include "gameNode.h"
class MenuScene : public gameNode
{
private:
	int SelectMenu;
	bool showName;		//맨처음 회사이름을 나타냄
	bool showLogo;		//그다음 게임로고를 나타냄
	bool showMenu;		//그다음 메뉴화면을 나타냄
	bool showKey;		//키보드 사용안내 화면을 나타냄
	int alphaValue;		//메뉴 알파렌더를 위한 변수
	bool fadeOut;		//화면이 어두워지게 할지 밝게 할지 결정
	float currentTime;	//시간을 저장하는 변수값
public:

	void keyboardInput();
	void changeScene();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	MenuScene();
	virtual ~MenuScene();
};

