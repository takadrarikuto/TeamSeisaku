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

	void SetScrollX(float sx) { m_scrollx = sx; }
	float GetScrollX() { return m_scrollx; }
	void SetScrollY(float sy) { m_scrolly = sy; }
	float GetScrollY() { return m_scrolly; }

private:
	float m_x1;//�w�i1�̈ʒu���

	float m_scrollx; //���X�N���[��
	float m_scrolly; //�c�X�N���[��
};