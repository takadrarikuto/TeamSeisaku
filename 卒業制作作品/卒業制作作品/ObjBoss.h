#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBoss : public CObj, public CBaseStatus
{
public:
	CObjBoss(float bx, float by);
	~CObjBoss() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_bx; //�ʒu�X�V
	float m_by;
	float e_x; //�G�l�~�[�o���ʒu
	float e_y;
	float m_bvx; //�{�X�ړ��x�N�g��
	float m_bvy;

	int m_Enemy_Generation; //�G�����p�x
	int m_Zombie_Restriction; //�]���r����������
	int m_Zombie_Restriction_max; //�]���r�����������ő�l
	int Ze_dst_flg_num; //�]���r�����_���`��؂�ւ��p�ϐ�
	bool Ze_dst_flg;  //�]���r�����_���`��؂�ւ��p�t���O

	float m_scrollx; //���X�N���[��
	float m_scrolly; //�c�X�N���[��

};