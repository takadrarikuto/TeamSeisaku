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

//�G�����������ݒ�p
	void SetZR(int zr) { m_Zombie_Restriction_num = zr; } //�]���r
	void SetBR(int br) { m_Bat_Enemy_Restriction_num = br; } //��
	void SetFLR(int flr) { m_Frie_Lizard_Restriction_num = flr; } //�΃g�J�Q
	void SetFBR(int fbr) { m_Frie_Bird_Restriction_num = fbr; } //�΂̒�

private:
	float m_bx; //�ʒu�X�V
	float m_by;
	float e_x; //�G�l�~�[�o���ʒu
	float e_y;
	float m_Enemy_Generation_x; //�]���r�������W�L�^
	float m_Enemy_Generation_y;
	float m_bvx; //�{�X�ړ��x�N�g��
	float m_bvy;

	//�G�����p�x
	int m_Zombie_Generation; //�]���r�����p�x
	int m_Bat_Enemy_Generation; //�啐����p�x
	int m_Frie_Lizard_Generation; //�΃g�J�Q�G�����p�x
	int m_Frie_Bird_Generation; //�΂̒��G�����p�x
	int m_Sphere_Type_Enemy_Generation; //���̌^�G�G�����p�x
//�]���r
	int m_Zombie_Restriction; //�]���r����������
	int m_Zombie_Restriction_num; //�]���r��������������
	int m_Zombie_Restriction_max; //�]���r�����������ő吔
	int m_Zombie_time_max; //�]���r�����^�C���ő�l
	int Ze_dst_flg_num; //�]���r�����_���`��؂�ւ��p�ϐ�
	bool Ze_dst_flg;  //�]���r�����_���`��؂�ւ��p�t���O
//��
	int m_Bat_Enemy_time_max; //�啐����^�C���ő�l
	int m_Bat_Enemy_Restriction; //�啐���������
	int m_Bat_Enemy_Restriction_num; //�啐�������������
	int m_Bat_Enemy_Restriction_max; //�啐����������ő吔
	int m_Bat_Enemy_co_num; //�啐������J�E���g�ϐ�
	float m_Bat_Enemy_x; //x�ʒu�C��
	float m_Bat_Enemy_y; //y�ʒu�C��
//�΃g�J�Q
	int m_Frie_Lizard_time_max; //�΃g�J�Q�����^�C���ő�l
	int m_Frie_Lizard_Restriction; //�΃g�J�Q����������
	int m_Frie_Lizard_Restriction_num; //�΃g�J�Q��������������
	int m_Frie_Lizard_Restriction_max; //�΃g�J�Q�����������ő�l
//�΂̒�
	int m_Frie_Bird_time_max; //�΂̒������^�C���ő�l
	int m_Frie_Bird_Restriction; //�΂̒�����������
	int m_Frie_Bird_Restriction_num; //�΂̒���������������
	int m_Frie_Bird_Restriction_max; //�΂̒������������ő�l
//���̌^�G
	int m_Sphere_Type_Enemy_Restriction; //���̌^�G������
	bool m_Sphere_Type_Enemy_Restriction_Stop_flg; //���̌^������~�t���O
	float m_Sphere_Type_Enemy_x; //x�ʒu�C��
	float m_Sphere_Type_Enemy_y; //y�ʒu�C��
//�~�[������
	bool m_Meme_Medium_Boss_Restriction_Stop_flg; //�~�[�����Ԑ�����~�t���O

	float m_scrollx; //���X�N���[��
	float m_scrolly; //�c�X�N���[��

};