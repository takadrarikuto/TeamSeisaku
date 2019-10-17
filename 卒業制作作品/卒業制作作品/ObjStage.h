#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
//�`��֌W�̒萔
#define GAME_HP_POS_X     (80)
#define GAME_HP_POS_Y     (15)
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
	int m_boss_hp;	//HP
	int m_stage_time;	//�X�e�[�W�^�C��

	float m_y1; //�ʒu���@1���ڗp
	float m_y2; //�ʒu���@2���ڗp
	float m_vy; //�ړ��x�N�g��

	int m_ani_frame;	//�`��t���[��
};
