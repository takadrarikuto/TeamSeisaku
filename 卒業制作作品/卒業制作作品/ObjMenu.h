#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjMenu : public CObj
{
public:
	CObjMenu() {};
	~CObjMenu() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	void BackDraw(float top, float left, float right, float bottom, float c[]);

private:
	bool m_key_flag;//�L�[�t���O
	int choose;
	int m_time;
	int m_time_s;

	int sg_pb;
	int ar_pb;
	int sr_pb;
	int rl_pb;
	int rg_pb;

	float m_and;		//�����x�����p
	bool m_andf;		//�����x�����p�t���O
	bool m_andf2;		//�����x�����p�t���O
	bool m_Scene_flg; //�V�[���ړ��t���O
};