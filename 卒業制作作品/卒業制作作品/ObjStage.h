#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
//�`��֌W�̒萔
#define GAME_HP_POS_X     (78)
#define GAME_HP_POS_Y     (5)
#define GAME_HP_FONT_SIZE (25)

#define GAME_MP_POS_X     (0)
#define GAME_MP_POS_Y     (25)
#define GAME_MP_FONT_SIZE (25)

#define GAME_TIME_POS_X     (13)
#define GAME_TIME_POS_Y     (27)
#define GAME_TIME_FONT_SIZE (25)

#define GAME_MESSAGE_POS_X     (200)
#define GAME_MESSAGE_POS_Y     (0)
#define GAME_MESSAGE_FONT_SIZE (20)

#define GAME_MESSAGE2_POS_X     (200)
#define GAME_MESSAGE2_POS_Y     (25)
#define GAME_MESSAGE2_FONT_SIZE (20)

#define GAME_ENEMY_KILLS_POS_X     (610)
#define GAME_ENEMY_KILLS_POS_Y     (15)
#define GAME_ENEMY_KILLS_FONT_SIZE (25)


//�I�u�W�F�N�g�F���j���[
class CObjStage :public CObj 
{
public:
	CObjStage() {};
	~CObjStage() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

private:
	int max_hp;	//HP�ő�l
	float m_px;			//�v���C���[�̍��WX
	float m_py;			//�v���C���[�̍��WX
	int m_posture;		//�p��
	int hero_hp;	//HP
	int hero_en;	//�ϋv��
	int m_boss_hp;	//HP
	int m_stage_time;	//�X�e�[�W�^�C��

	int m_ani_frame;	//�`��t���[��

	//�e�c��e�����擾�p�ϐ�(������)
	int hg_pb_e;
	int sg_pb_e;
	int ar_pb_e;
	int sr_pb_e;
	int rl_pb_e;
	int rg_pb_e;
	int gre_pb_e;

	//�e�c��e�����擾�p�ϐ�(�S��)
	int sg_pb; 
	int ar_pb; 
	int sr_pb; 
	int rl_pb; 
	int rg_pb; 
	int gre_pb;

	float m_bx; //�ʒu�X�V
	float m_by;
	float e_x; //�G�l�~�[�o���ʒu
	float e_y;
	float m_Item_Generation_x; //�]���r�������W�L�^
	float m_Item_Generation_y;
	float m_bvx; //�{�X�ړ��x�N�g��
	float m_bvy;

	//�G�����p�x
	int m_Heal_Generation; //�񕜃A�C�e�������p�x
	//int m_Bat_Enemy_Generation; //�啐����p�x
	//int m_Frie_Lizard_Generation; //�΃g�J�Q�G�����p�x
	//int m_Frie_Bird_Generation; //�΂̒��G�����p�x
	//int m_Sphere_Type_Enemy_Generation; //���̌^�G�G�����p�x

	int m_Heal_Item_time_max; //�񕜃A�C�e�������^�C���ő�l
	int m_Heal_Item_Restriction; //�񕜃A�C�e������������
	int m_Heal_Item_Restriction_max; //�񕜃A�C�e�������������ő�l
	int m_Heal_Item_co_num; //�񕜃A�C�e���������J�E���g�ϐ�
};
