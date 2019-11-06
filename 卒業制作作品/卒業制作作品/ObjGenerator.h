#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGenerator :public CObj, public CBaseStatus
{
public:
	CObjGenerator(float x, float y);
	~CObjGenerator() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー
	
	float GetGenX() { return m_Genx; } //x位置情報取得用
	float GetGenY() { return m_Geny; } //y位置情報取得用
	float GetGenHitX() { return m_HitSize_x; } //HitBox xサイズ取得用
	float GetGenHitY() { return m_HitSize_y; } //HitBox yサイズ取得用

private:
	float m_Genx; //位置情報
	float m_Geny;
	float m_Genvx; //位置更新
	float m_Genvy;

	float m_HitSize_x; //HitBoxサイズ
	float m_HitSize_y;

};