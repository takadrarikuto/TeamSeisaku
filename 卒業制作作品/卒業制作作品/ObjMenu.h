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

private:
	bool m_key_flag;//�L�[�t���O
	int choose;
	int m_time;
	int m_time_s;
	float m_and;		//�����x�����p
	bool m_andf;		//�����x�����p�t���O
	bool m_andf2;		//�����x�����p�t���O
	bool m_Scene_flg; //�V�[���ړ��t���O
};