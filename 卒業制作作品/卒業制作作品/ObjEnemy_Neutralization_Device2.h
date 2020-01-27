#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjEnemy_Neutralization_Device2 :public CObj, public CBaseStatus
{
public:
	CObjEnemy_Neutralization_Device2(float x, float y);
	~CObjEnemy_Neutralization_Device2() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetEndX() { return m_Enemy_Neu_Dev2x; } //x位置情報取得用
	float GetEndY() { return m_Enemy_Neu_Dev2y; } //y位置情報取得用
	float GetEndHitX() { return m_Enemy_Neu_Dev2_HitSize_x; }  //HitBox xサイズ取得用
	float GetEndHitY() { return m_Enemy_Neu_Dev2_HitSize_y; }  //HitBox yサイズ取得用
	
	bool Get_Deat2() { return m_END2_death_flg; } //死亡フラグ取得用

	void Set_Deat2(bool end2_d) { m_END2_death_flg = end2_d; } //死亡フラグ設定用
private:
	float m_Enemy_Neu_Dev2x; //位置情報
	float m_Enemy_Neu_Dev2y;

	float m_Enemy_Neu_Dev2_HitSize_x;  //HitBoxサイズ
	float m_Enemy_Neu_Dev2_HitSize_y;

	int m_Font_time; //フォント表示タイム

	bool m_END2_death_flg; //死亡フラグ

};