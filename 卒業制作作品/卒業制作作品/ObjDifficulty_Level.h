#pragma once
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

////�}�E�X�N���b�N�̃��C���J�ځi���񂢁j
#define GAME_EASY_POS_X (400) //�ȒP
#define GAME_EASY_POS_Y (200) 
#define GAME_EASY_FONT_SIZE (45)

#define GAME_NORMAL_POS_X (400) //����
#define GAME_NORMAL_POS_Y (200)
#define GAME_NORMAL_FONT_SIZE (45)

#define GAME_HARD_POS_X (400) //���
#define GAME_HARD_POS_Y (460)
#define GAME_HARD_FONT_SIZE (45)

#define GAME_EXIT_POS_X (400) //�^�C�g���w�߂�
#define GAME_EXIT_POS_Y (460)
#define GAME_EXIT_FONT_SIZE (45)


////�`��֌W�̒萔
//#define TITLE_POS_X (200)
//#define TITLE_POS_Y (250)
//#define TITLE_FONT_SIZE (40)
//
//#define CLICK_START_POS_X (230)
//#define CLICK_START_POS_Y (400)
//#define CLICK_START_FONT_SIZE (30)
//
//#define CLICK_RESET_POS_X (680)
//#define CLICK_RESET_POS_Y (380)
//#define CLICK_RESET_FONT_SIZE (16)

//�I�u�W�F�N�g:�^�C�g��
class ObjDifficulty_Level :public CObj
{
public:
	ObjDifficulty_Level() {};
	~ObjDifficulty_Level() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[


private:
	bool m_key_flag; //�L�[�t���O
	float m_mou_x;  //�}�E�X�̈ʒuX
	float m_mou_y;  //�}�E�X�̈ʒuY
	bool m_mou_r;   //�}�E�X�̉E�{�^��
	bool m_mou_l;   //�}�E�X�̍��{�^��
	bool  m_f;     //�e�۔��ː���p
	float m_and;		//�����x�����p
	bool m_andf;		//�����x�����p�t���O
	int m_time;

};
