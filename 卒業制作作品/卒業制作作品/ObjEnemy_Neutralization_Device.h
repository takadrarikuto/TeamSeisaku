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

	float GetEndX() { return m_Enemy_Neu_Devx; } //x位置情報取得用
	float GetEndY() { return m_Enemy_Neu_Devy; } //y位置情報取得用
	float GetEndHitX() { return m_Enemy_Neu_Dev_HitSize_x; }  //HitBox xサイズ取得用
	float GetEndHitY() { return m_Enemy_Neu_Dev_HitSize_y; }  //HitBox yサイズ取得用
	
	bool Get_Deat() { return m_END_death_flg; } //死亡フラグ取得用

	void Set_Deat(bool end_d) { m_END_death_flg = end_d; } //死亡フラグ設定用
private:
	float m_Enemy_Neu_Devx; //位置情報
	float m_Enemy_Neu_Devy;

	float m_Enemy_Neu_Dev_HitSize_x;  //HitBoxサイズ
	float m_Enemy_Neu_Dev_HitSize_y;

	int m_Font_time; //フォント表示タイム
					
	bool m_END_death_flg; //死亡フラグ

};