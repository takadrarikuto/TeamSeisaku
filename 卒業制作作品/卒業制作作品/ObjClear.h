#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:�Q�[���N���A
class CObjClear : public CObj
{
public:
	CObjClear() {};
	~CObjClear() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:
	bool m_key_flag;//�L�[�t���O
	float m_and;		//�����x�����p
	bool m_andf;		//�����x�����p�t���O
	int choose;
	int m_time;
};