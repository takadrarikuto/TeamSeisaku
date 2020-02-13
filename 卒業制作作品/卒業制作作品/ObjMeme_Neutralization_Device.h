#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjMeme_Neutralization_Device :public CObj, public CBaseStatus
{
public:
	CObjMeme_Neutralization_Device(float x, float y);
	~CObjMeme_Neutralization_Device() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetMndX() { return m_Meme_Neu_Devx; } //x�ʒu���擾�p
	float GetMndY() { return m_Meme_Neu_Devy; } //y�ʒu���擾�p
	float GetMndHitX() { return m_Meme_Neu_Dev_HitSize_x; }  //HitBox x�T�C�Y�擾�p
	float GetMndHitY() { return m_Meme_Neu_Dev_HitSize_y; }  //HitBox y�T�C�Y�擾�p

	bool GetMeme_death() { return m_Meme_death_flg; } //���S�t���O�擾�p

	void SetMeme_death(bool m_md) { m_Meme_death_flg = m_md; } //���S�t���O�ݒ�p

private:
	float m_Meme_Neu_Devx; //�ʒu���
	float m_Meme_Neu_Devy;

	float m_Meme_Neu_Dev_HitSize_x;  //HitBox�T�C�Y
	float m_Meme_Neu_Dev_HitSize_y;

	int m_Font_time; //�t�H���g�\���^�C��

	bool m_Meme_death_flg; //���S�t���O
};