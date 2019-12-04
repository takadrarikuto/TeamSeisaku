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

//��������ϐ�
	//X����
	int m_Gene_distance_X; //���d�@��������ϐ�
	int m_END_distance_X; //�G���͉����u��������ϐ�
	int m_Gene2_distance_X; //���d�@2��������ϐ�
	int m_END2_distance_X; //�G���͉����u2��������ϐ�
	int m_MND_distance_X; //�΃~�[�����Ԗ��͉����u��������ϐ�
	int m_Tool_distance_X; //�c�[���{�b�N�X��������ϐ�
	//Y����
	int m_Gene_distance_Y; //���d�@��������ϐ�
	int m_END_distance_Y; //�G���͉����u��������ϐ�
	int m_Gene2_distance_Y; //���d�@2��������ϐ�
	int m_END2_distance_Y; //�G���͉����u2��������ϐ�
	int m_MND_distance_Y; //�΃~�[�����Ԗ��͉����u��������ϐ�
	int m_Tool_distance_Y; //�c�[���{�b�N�X��������ϐ�
	//�΂ߕ���
	int m_Gene_distance_r; //���d�@��������ϐ�
	int m_END_distance_r; //�G���͉����u��������ϐ�
	int m_Gene2_distance_r; //���d�@2��������ϐ�
	int m_END2_distance_r; //�G���͉����u2��������ϐ�
	int m_MND_distance_r; //�΃~�[�����Ԗ��͉����u��������ϐ�
	int m_Tool_distance_r; //�c�[���{�b�N�X��������ϐ�

};