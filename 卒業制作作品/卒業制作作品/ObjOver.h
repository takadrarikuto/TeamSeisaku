#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�`��֌W�̒萔

#define GAME_OVER_X (90)
#define GAME_OVER_Y (125)
#define GAME_OVER_FONT_SIZE (58)

#define GAME_YES_X (400)
#define GAME_YES_Y (350)
#define GAME_YES_FONT_SIZE (50)

#define GAME_NO_X (400)
#define GAME_NO_Y (460)
#define GAME_NO_FONT_SIZE (50)

#define RANKING_POS_X (600)
#define RANKING_POS_Y (0)
#define RANKING_FONT_SIZE (24)
#define RANKING_SCORE_MAX (15)
#define STR_MAX (256)
#define SCORE_INIT (1)
#define SCORE_POS_X (670)
#define SCORE_POS_Y (24)
#define SCORE_POINT_MAX (100)
#define SCORE_INTERVAL (24)
#define SCORE_FONT_SIZE (12)

#define CLICK_START_POS_X (230)
#define CLICK_START_POS_Y (400)
#define CLICK_START_FONT_SIZE (30)

#define CLICK_RESET_POS_X (680)
#define CLICK_RESET_POS_Y (380)
#define CLICK_RESET_FONT_SIZE (16)


//�I�u�W�F�N�g:�N���A
class CObjOver : public CObj
{
public:
	CObjOver() {};
	~CObjOver() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
	//void BackDraw(float top, float left, float right, float bottom, float c[]);
private:
	bool m_key_flag;//�L�[�t���O
	int choose;
	int m_time;
	int m_time_s;
	float m_and;		//�����x�����p
	bool m_andf;		//�����x�����p�t���O
	bool m_andf2;		//�����x�����p�t���O
};