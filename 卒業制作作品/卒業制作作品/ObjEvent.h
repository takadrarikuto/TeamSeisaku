#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

#define EVENT_INSTRUCTION 180

class CObjEvent :public CObj, public CBaseStatus
{
public:
	CObjEvent() {};
	~CObjEvent() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	bool GetEveTimPena() { return m_Event_TimePenalty; } //�C�x���g�^�C���y�i���e�B�擾�p
	int GetApp_Rand() { return m_App_Rand_Flg; } //���u�̏�C�x���g���̑��u�����_���I���擾�p
	int GetEveIns() { return m_Event_Instruction_time; } //�C�x���g�w���\���^�C���擾�p

	void SetEveTimPena(bool T_P) { m_Event_TimePenalty = T_P; } //�C�x���g�^�C���y�i���e�B�ݒ�p

private:
	int m_Event_time;	//�C�x���g����
	bool m_Event_TimePenalty; //�C�x���g�^�C���y�i���e�B
	bool m_Event_time_flg; //�C�x���g�t���O
	int m_Event_Instruction_time; //�C�x���g�w���\���^�C��

	int m_App_Rand_Flg; //���u�̏�C�x���g���̑��u�����_���I��

};