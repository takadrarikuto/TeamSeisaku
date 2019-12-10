#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjMeme_Neutralization_Device :public CObj, public CBaseStatus
{
public:
	CObjMeme_Neutralization_Device(float x, float y);
	~CObjMeme_Neutralization_Device() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetMndX() { return m_Meme_Neu_Devx; } //x位置情報取得用
	float GetMndY() { return m_Meme_Neu_Devy; } //y位置情報取得用
	float GetMndHitX() { return m_Meme_Neu_Dev_HitSize_x; }  //HitBox xサイズ取得用
	float GetMndHitY() { return m_Meme_Neu_Dev_HitSize_y; }  //HitBox yサイズ取得用

private:
	float m_Meme_Neu_Devx; //位置情報
	float m_Meme_Neu_Devy;

	float m_Meme_Neu_Dev_HitSize_x;  //HitBoxサイズ
	float m_Meme_Neu_Dev_HitSize_y;

	int m_Font_time; //フォント表示タイム
};