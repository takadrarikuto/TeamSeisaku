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

	//int GetTIncrease() { return m_time_Increase; } //�^�C�������y�i���e�B�擾�p
	bool GetTStop() { return m_Stop_flg; } //���Ԓ�~�t���O�擾�p
	bool GetTStart() { return m_Start_flg; } //����J�n�t���O�擾�p

	bool GetGenFlg() { return m_Gen_flg; } //���d�@�N���t���O�擾�p
	bool GetENDFlg() { return m_END_flg; } //�G���͉����u�t���O�擾�p
	bool GetMNDFlg() { return m_MND_flg; } //�~�[�����Ԗ��͉����u�t���O�擾�p
	bool GetRepFlg() { return m_Repairing_flg; } //���u�C���C�x���g�t���O�擾�p

	//void SetTIncrease(int increase_t) { m_time_Increase = increase_t; } //�^�C�������y�i���e�B�ݒ�p
	void SetTStop(bool stop_t) { m_Stop_flg = stop_t; }  //���Ԓ�~�t���O�ݒ�p
	void SetTStart(bool start_t) { m_Start_flg = start_t; } //����J�n�t���O�ݒ�p

	void SetGenFlg(bool gen_f) { m_Gen_flg = gen_f; } //���d�@�N���t���O�ݒ�p
	void SetENDFlg(bool end_f) { m_END_flg = end_f; } //�G���͉����u�t���O�ݒ�p
	void SetMNDFlg(bool mnd_f) { m_MND_flg = mnd_f; } //�~�[�����Ԗ��͉����u�t���O�ݒ�p
	void SetRepFlg(bool rep_f) { m_Repairing_flg = rep_f; } //���u�C���C�x���g�t���O�ݒ�p

	void SetTimeFlag(bool b) { m_flag_time = b; } 
private:
	int m_time;		//����
	int m_time_stop; //���Ԓ�~
	int m_time_event; //�C�x���g�J�n����
	int m_Event_Rand_num; //�C�x���g�����_���ϐ�
	//int m_time_Increase; //�^�C�������y�i���e�B

	bool m_flag_time;//���Ԍv���X�^�[�g�t���O
	bool m_Stop_flg; //�v����~�t���O
	bool m_Start_flg; //����J�n�t���O	

	bool m_Gen_flg; //���d�@�N���t���O
	bool m_END_flg; //�G���͉����u�t���O
	bool m_MND_flg; //�~�[�����Ԗ��͉����u�t���O
	bool m_Repairing_flg; //���u�C���C�x���g�t���O

	bool m_Tool_Box_flg; //�c�[���{�b�N�X�����t���O
};
