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

	bool GetMenu() { return Menu_flg; } //���j���[ONOFF�t���O�擾�p
	bool GetMenuKey() { return m_key_flag_menu; } //���j���[�L�[����p�t���O�擾�p

	void BackDraw(float top, float left, float right, float bottom, float c[]);

	void SetMenu(bool m_f) { Menu_flg = m_f; } //���j���[ONOFF�t���O�ݒ�p
	void SetMenuKey(bool m_mk) { m_key_flag_menu = m_mk; } //���j���[�L�[����p�t���O�ݒ�p

private:
	
	bool Menu_flg; //���j���[ONOFF�t���O

	bool m_key_flag;//�L�[�t���O
	int choose;
	int m_time;
	int m_time_s;

	//�e�c��e�����擾�p�ϐ�(�S��)
	int sg_pb_me;
	int ar_pb_me;
	int sr_pb_me;
	int rl_pb_me;
	int rg_pb_me;
	int gre_pb_me;

	//�e�c��e�����擾�p�ϐ�(�����[�h�p)
	int sg_pb_r;
	int ar_pb_r;
	int sr_pb_r;
	int rl_pb_r;
	int rg_pb_r;
	int gre_pb_r;

	float m_and;		//�����x�����p
	bool m_andf;		//�����x�����p�t���O
	bool m_andf2;		//�����x�����p�t���O
	bool m_Scene_flg; //�V�[���ړ��t���O					  
	bool m_key_flag_menu; //���j���[�L�[����p�t���O

};