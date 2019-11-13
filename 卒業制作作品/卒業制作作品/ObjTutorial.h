#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�`��֌W�̒萔
#define TITLE_POS_X (200)
#define TITLE_POS_Y (250)
#define TITLE_FONT_SIZE (40)

#define CLICK_START_POS_X (230)
#define CLICK_START_POS_Y (400)
#define CLICK_START_FONT_SIZE (30)

#define CLICK_RESET_POS_X (680)
#define CLICK_RESET_POS_Y (380)
#define CLICK_RESET_FONT_SIZE (16)

//�I�u�W�F�N�g:�^�C�g��
class CObjTutorial :public CObj
{
	public:
		CObjTutorial() {};
		~CObjTutorial() {};
		void Init();    //�C�j�V�����C�Y
		void Action();  //�A�N�V����
		void Draw();    //�h���[
	private:
		int max_hp;	//HP�ő�l
		float m_px;			//�v���C���[�̍��WX
		float m_py;			//�v���C���[�̍��WX
		int m_posture;		//�p��
		int hero_hp;	//HP
		int m_boss_hp;	//HP
		int m_stage_time;	//�X�e�[�W�^�C��

		int m_ani_frame;	//�`��t���[��

		bool m_key_flag; //�L�[�t���O
		bool  m_f;     //�e�۔��ː���p
		float m_and;		//�����x�����p
		bool m_andf;		//�����x�����p�t���O
		int choose;
		int m_time;
		int m_tuto_time;

		//�e�c��e�����擾�p�ϐ�(������)
		int hg_pb_e;
		int sg_pb_e;
		int ar_pb_e;
		int sr_pb_e;
		int rl_pb_e;
		int rg_pb_e;
		int gre_pb_e;

		int zombie_count;
};
