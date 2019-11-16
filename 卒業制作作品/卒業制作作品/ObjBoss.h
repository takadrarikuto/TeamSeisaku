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
	float m_Enemy_Generation_x; //�]���r�������W�L�^
	float m_Enemy_Generation_y;
	float m_bvx; //�{�X�ړ��x�N�g��
	float m_bvy;

	int m_Enemy_Generation; //�G�����p�x
//�]���r
	int m_Zombie_Restriction; //�]���r����������
	int m_Zombie_Restriction_max; //�]���r�����������ő�l
	int m_Zombie_time_max; //�]���r�����^�C���ő�l
	int Ze_dst_flg_num; //�]���r�����_���`��؂�ւ��p�ϐ�
	bool Ze_dst_flg;  //�]���r�����_���`��؂�ւ��p�t���O
//�΂̒�
	int m_Frie_Bird_time_max; //�΂̒������^�C���ő�l
	int m_Frie_Bird_Restriction; //�΂̒�����������
	int m_Frie_Bird_Restriction_max; //�΂̒������������ő�l
//�΃g�J�Q
	int m_Frie_Lizard_time_max; //�΃g�J�Q�����^�C���ő�l
	int m_Frie_Lizard_Restriction; //�΃g�J�Q����������
	int m_Frie_Lizard_Restriction_max; //�΃g�J�Q�����������ő�l

	float m_scrollx; //���X�N���[��
	float m_scrolly; //�c�X�N���[��

};