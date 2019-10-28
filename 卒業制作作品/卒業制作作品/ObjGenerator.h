#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGenerator :public CObj, public CBaseStatus
{
public:
	CObjGenerator(float x, float y);
	~CObjGenerator() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[
	
	bool GetTS() { return m_Starp_flg; } //���Ԓ�~�t���O�擾�p

private:
	float m_Genx; //�ʒu���
	float m_Geny;
	float m_Genvx; //�ʒu�X�V
	float m_Genvy;

	bool m_Starp_flg; //�v���J�n�t���O

	//�㉺���E�ʓ����蔻��m�F�t���O
	bool m_UpHit_flg;    //��
	bool m_DownHit_flg;	 //��
	bool m_LeftHit_flg;	 //��
	bool m_LightHit_flg; //�E
};