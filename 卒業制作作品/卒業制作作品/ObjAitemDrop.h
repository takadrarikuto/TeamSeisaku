#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjAitemDrop :public CObj, public CBaseStatus
{
public:
	CObjAitemDrop() {};
	~CObjAitemDrop() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetAitemDrop() { return m_Aitem_Drop_flg; } //�A�C�e���h���b�v�t���O�擾�p
	void SetAitemDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //�A�C�e���h���b�v�t���O�ݒ�p

private:
	bool m_Aitem_Drop_flg; //�A�C�e���h���b�v�t���O
	int m_Aitem_Rand_num; //�A�C�e�������_���I��ϐ�

};