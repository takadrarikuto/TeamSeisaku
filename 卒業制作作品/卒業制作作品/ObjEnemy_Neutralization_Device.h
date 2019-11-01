#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjEnemy_Neutralization_Device :public CObj, public CBaseStatus
{
public:
	CObjEnemy_Neutralization_Device(float x, float y);
	~CObjEnemy_Neutralization_Device() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetGenX() { return m_Enemy_Neu_Devx; } //x位置情報取得用
	float GetGenY() { return m_Enemy_Neu_Devy; } //y位置情報取得用

private:
	float m_Enemy_Neu_Devx; //位置情報
	float m_Enemy_Neu_Devy;
	float m_Enemy_Neu_Dev_vx; //位置更新
	float m_Enemy_Neu_Dev_vy;

	bool m_Start_flg; //計測開始フラグ

};