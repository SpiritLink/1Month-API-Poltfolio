#pragma once

#include "gameNode.h"
class MenuScene : public gameNode
{
private:
	int SelectMenu;
	int selectFile;		//현재 고른 세이브 파일을 표시해줍니다.
	bool showName;		//맨처음 회사이름을 나타냄
	bool showLogo;		//그다음 게임로고를 나타냄
	bool showMenu;		//그다음 메뉴화면을 나타냄
	bool showKey;		//키보드 사용안내 화면을 나타냄
	int alphaValue;		//메뉴 알파렌더를 위한 변수
	bool fadeOut;		//화면이 어두워지게 할지 밝게 할지 결정
	float currentTime;	//시간을 저장하는 변수값
	bool deleteFile;	//세이브 파일 삭제를 위한 변수

	int MAXHP[3];		//세이브 목록에 표시하기 위한 변수
	int HP[3];			//세이브 목록에 표시하기 위한 변수
	int MP[3];			//세이브 목록에 표시하기 위한 변수
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyboardInput();
	void changeScene();
	void initData();	//파일에서 데이터를 읽어 들인뒤 지역변수에 저장합니다.
	MenuScene();
	virtual ~MenuScene();
};

