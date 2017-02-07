#include "stdafx.h"
#include "collision.h"


HRESULT collision::init(player* PL, attackManager* ATK, enemyManager* EMG)
{
	_player = PL;			//플레이어 연동
	_attackManager = ATK;	//공격 매니저 연동
	_enemyManager = EMG;	//적 매니저 연동
	return S_OK;
}

void collision::release()
{
}

void collision::update()
{
	//흐름은 어떻게 할 것인가
	//공격	< - > 적
	//공격	< - > 플레이어
	//적		< - > 플레이어
	//3단계의 흐름으로 진행하자.
	//데미지는 무조건 1씩 들어간다.
}

void collision::render()
{
}

collision::collision()
{
}


collision::~collision()
{
}
