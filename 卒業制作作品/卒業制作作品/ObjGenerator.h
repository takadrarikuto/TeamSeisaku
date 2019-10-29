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

private:
	float m_Genx; //位置情報
	float m_Geny;
	float m_Genvx; //位置更新
	float m_Genvy;

	bool m_Start_flg; //計測開始フラグ

};