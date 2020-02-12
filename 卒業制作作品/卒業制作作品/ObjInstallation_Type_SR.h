#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL; 

#define REPLENIShHMENT_FONT_TIME 120 //再補充完了フォント表示タイム

class CObjInstallation_Type_SR :public CObj, public CBaseStatus
{
public:
	CObjInstallation_Type_SR(float x, float y);
	~CObjInstallation_Type_SR() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetGenX() { return m_IT_SRx; } //x位置情報取得用
	float GetGenY() { return m_IT_SRy; } //y位置情報取得用
	float GetGenHitX() { return m_HitSize_x; } //HitBox xサイズ取得用
	float GetGenHitY() { return m_HitSize_y; } //HitBox yサイズ取得用

	bool GetRepFontflg() { return m_Replenishment_Font_flg; } //再補充完了フォント表示フラグ取得用

private:
	float m_IT_SRx; //位置情報
	float m_IT_SRy;
	float m_IT_SRvx; //位置更新
	float m_IT_SRvy;

	float m_HitSize_x; //HitBoxサイズ
	float m_HitSize_y;

	int m_Font_time; //フォント表示タイム

	int m_IT_SR_num_max; //設置型スナイパーライフルの弾数回復量最大値

	bool m_Replenishment_flg; //補充フラグ
	int m_Replenishment_time; //再補充タイム
	bool m_Replenishment_Font_flg; //再補充完了フォント表示フラグ
	int m_Replenishment_Font_time; //再補充完了フォント表示タイム
};