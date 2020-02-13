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

	bool GetEveMiss() { return m_EveMiss_flg; } //���Ԓ�~�t���O�擾�p
	bool GetEveSuc() { return m_EveSuccess_flg; } //�C�x���g�����t���O�擾�p

	bool GetEveTimPena() { return m_Event_TimePenalty; } //�C�x���g�^�C���y�i���e�B�擾�p
	bool GetEvePena_Enemy() { return m_EventPenalty_Enemy_flg; } //�C�x���g�y�i���e�B(���̌^�G)�t���O�擾�p
	bool GetEvePena_Meme() { return m_EventPenalty_Meme_flg; } //�C�x���g�y�i���e�B(�~�[������)�t���O

	int GetApp_Rand() { return m_App_Rand_Flg; } //���u�̏�C�x���g���̑��u�����_���I���擾�p
	int GetEveIns() { return m_Event_Instruction_time; } //�C�x���g�w���\���^�C���擾�p

	void SetEveTimPena(bool T_P) { m_Event_TimePenalty = T_P; } //�C�x���g�^�C���y�i���e�B�ݒ�p
	void SetApp_Rand(int app_r_f) { m_App_Rand_Flg = app_r_f; } //���u�̏�C�x���g���̑��u�����_���I��ݒ�p
	void SetEvePena_Enemy(bool P_E) { m_EventPenalty_Enemy_flg = P_E; } //�C�x���g�y�i���e�B(���̌^�G)�t���O�ݒ�p
	void SetEvePena_Meme(bool P_M) { m_EventPenalty_Meme_flg = P_M; } //�C�x���g�y�i���e�B(�~�[������)�t���O�ݒ�p

	void SetEveMiss(bool EveMiss) { m_EveMiss_flg = EveMiss; } //���Ԓ�~�t���O�ݒ�p
	void SetEveSuc(bool EveSucc) { m_EveSuccess_flg = EveSucc; } //�C�x���g�����t���O�ݒ�p
private:
	int m_Event_time;	//�C�x���g����
	bool m_Event_TimePenalty; //�C�x���g�^�C���y�i���e�B
	bool m_Event_time_flg; //�C�x���g�t���O
	bool m_EveSuccess_flg; //�C�x���g�����t���O						   
	bool m_EveMiss_flg; //�C�x���g���s�t���O

	int m_Event_Instruction_time; //�C�x���g�w���\���^�C��

	bool m_EventPenalty_Enemy_flg; //�C�x���g�y�i���e�B(���̌^�G)�t���O
	bool m_EventPenalty_Meme_flg; //�C�x���g�y�i���e�B(�~�[������)�t���O

	int m_App_Rand_Flg; //���u�̏�C�x���g���̑��u�����_���I��

};