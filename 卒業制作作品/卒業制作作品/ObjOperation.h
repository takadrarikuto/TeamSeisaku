#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�`��֌W�̒萔
#define TITLE_POS_X (200)
#define TITLE_POS_Y (250)
#define TITLE_FONT_SIZE (40)

//�I�u�W�F�N�g:�^�C�g��
class CObjOperation :public CObj
{
public:
	CObjOperation() {};
	~CObjOperation() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:
	bool m_key_flag; //�L�[�t���O
	bool  m_f;     //�e�۔��ː���p
	float m_and;		//�����x�����p
	bool m_andf;		//�����x�����p�t���O
	int choose;
	int m_time;
};
