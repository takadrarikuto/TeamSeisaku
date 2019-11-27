#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C��
class CObjTime :public CObj
{
public:
	CObjTime() {};
	~CObjTime() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	bool GetTStop() { return m_Stop_flg; } //���Ԓ�~�t���O�擾�p
	bool GetTStart() { return m_Start_flg; } //����J�n�t���O�擾�p

	bool GetGenFlg() { return m_Gen_flg; } //���d�@�N���t���O�擾�p
	bool GetENDFlg() { return m_END_flg; } //�G���͉����u�t���O�擾�p
	bool GetMNDFlg() { return m_MND_flg; } //�~�[�����Ԗ��͉����u�t���O�擾�p

	void SetTStop(bool stop_t) { m_Stop_flg = stop_t; }  //���Ԓ�~�t���O�ݒ�p
	void SetTStart(bool start_t) { m_Start_flg = start_t; } //����J�n�t���O�ݒ�p

	void SetGenFlg(bool gen_f) { m_Gen_flg = gen_f; } //���d�@�N���t���O�ݒ�p
	void SetENDFlg(bool end_f) { m_END_flg = end_f; } //�G���͉����u�t���O�ݒ�p
	void SetMNDFlg(bool mnd_f) { m_MND_flg = mnd_f; } //�~�[�����Ԗ��͉����u�t���O�ݒ�p

	void SetTimeFlag(bool b) { m_flag_time = b; } 
private:
	int m_time;		//����
	int m_time_event; //�C�x���g�J�n����
	int m_Event_Rand_num; //�C�x���g�����_���ϐ�

	bool m_flag_time;//���Ԍv���X�^�[�g�t���O
	bool m_Stop_flg; //�v����~�t���O
	bool m_Start_flg; //����J�n�t���O

	bool m_Gen_flg; //���d�@�N���t���O
	bool m_END_flg; //�G���͉����u�t���O
	bool m_MND_flg; //�~�[�����Ԗ��͉����u�t���O
	 
};
