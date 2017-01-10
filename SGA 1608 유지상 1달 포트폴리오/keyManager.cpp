#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; ++i)
	{
		this->setKeyDown(i, false);
		this->setKeyUp(i, false);
	}

	return S_OK;
}
void keyManager::release()
{

}

//0x0000 : 이전에 누른 적이 없고 호출 시점에 안 눌린 상태
//0x8000 : 이전에 누른 적이 없고 호출 시점에 눌린 상태
//0x8001 : 이전에 누른 적이 있고 호출 시점에 눌린 상태
//0x0001 : 이전에 누른 적이 있고 호출 시점에 안 눌린 상태

//키가 한번만 눌렸는지 검사
bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//key번째 배열이 false상태면 == 눌려져 있지 않으면
		if (!this->getKeyDown()[key])
		{
			//눌러준다!~!!
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);
	return false;
}

//키를 눌렀다가 떼었을 때 검사
bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

//키를 누르고 있을 때 계속 검사
bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

//눌렀다가 떼면 true, 다시 눌렀다가 떼면 false... 무한반복
bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
