#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g :�w�i
class C0bjBackground : public CObj
{
public:
	C0bjBackground() {};
	~C0bjBackground() {};

	void Init();   //�C��V�����C�Y
	void Action();	//�A�N�V����
	void Draw();    //�h���[

	void SetScrollx(float sx) { m_xscroll = sx; }
	float GetScrollx() { return m_xscroll; }
	void SetScrolly(float sy) { m_yscroll = sy; }
	float GetScrolly() { return m_yscroll; }

private:
	float m_x1;//�w�i1�̈ʒu���

	float m_xscroll; //���X�N���[��
	float m_yscroll; //�c�X�N���[��
};