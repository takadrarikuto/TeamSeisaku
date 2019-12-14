#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

#define REPLENIShHMENT_TIME 300 //再補充タイム
#define REPLENIShHMENT_FONT_TIME 120 //再補充完了フォント表示タイム

class CObjInstallation_Type_ShotGun :public CObj, public CBaseStatus
{
public:
	CObjInstallation_Type_ShotGun(float x, float y);
	~CObjInstallation_Type_ShotGun() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetGenX() { return m_IT_SHGx; } //x位置情報取得用
	float GetGenY() { return m_IT_SHGy; } //y位置情報取得用
	float GetGenHitX() { return m_HitSize_x; } //HitBox xサイズ取得用
	float GetGenHitY() { return m_HitSize_y; } //HitBox yサイズ取得用

	bool GetRepFontflg() { return m_Replenishment_Font_flg; } //再補充完了フォント表示フラグ取得用

private:
	float m_IT_SHGx; //位置情報
	float m_IT_SHGy;
	float m_IT_SHGvx; //位置更新
	float m_IT_SHGvy;

	float m_HitSize_x; //HitBoxサイズ
	float m_HitSize_y;

	bool m_Replenishment_flg; //補充フラグ	
	int m_Replenishment_time; //再補充タイム
	bool m_Replenishment_Font_flg; //再補充完了フォント表示フラグ
	int m_Replenishment_Font_time; //再補充完了フォント表示タイム
};