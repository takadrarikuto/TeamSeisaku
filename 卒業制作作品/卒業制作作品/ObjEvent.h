#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjEvent :public CObj, public CBaseStatus
{
public:
	CObjEvent() {};
	~CObjEvent() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	bool GetEveTimPena() { return m_Event_TimePenalty; } //�C�x���g�^�C���y�i���e�B�擾�p

	void SetEveTimPena(bool E_TP) { m_Event_TimePenalty = E_TP; } //�C�x���g�^�C���y�i���e�B�ݒ�p

private:
	int m_Event_time;	//�C�x���g����
	bool m_Event_TimePenalty; //�C�x���g�^�C���y�i���e�B
	bool m_Event_time_flg; //�C�x���g�t���O

};