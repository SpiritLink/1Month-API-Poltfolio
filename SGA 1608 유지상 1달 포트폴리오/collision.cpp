#include "stdafx.h"
#include "collision.h"


HRESULT collision::init(player* PL, attackManager* ATK, enemyManager* EMG)
{
	_player = PL;			//�÷��̾� ����
	_attackManager = ATK;	//���� �Ŵ��� ����
	_enemyManager = EMG;	//�� �Ŵ��� ����
	return S_OK;
}

void collision::release()
{
}

void collision::update()
{
	//�帧�� ��� �� ���ΰ�
	//����	< - > ��
	//����	< - > �÷��̾�
	//��		< - > �÷��̾�
	//3�ܰ��� �帧���� ��������.
	//�������� ������ 1�� ����.
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
