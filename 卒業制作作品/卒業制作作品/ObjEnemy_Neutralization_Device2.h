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

	float GetEndX() { return m_Enemy_Neu_Devx; } //x位置情報取得用
	float GetEndY() { return m_Enemy_Neu_Devy; } //y位置情報取得用
	float GetEndHitX() { return m_Enemy_Neu_Dev_HitSize_x; }  //HitBox xサイズ取得用
	float GetEndHitY() { return m_Enemy_Neu_Dev_HitSize_y; }  //HitBox yサイズ取得用

	bool GetDeath() { return m_END_death_flg; } //無力化装置起動フラグ取得用

	void SetDeath(bool END_De_flg) { m_END_death_flg = END_De_flg; } //無力化装置起動フラグ設定用
	
private:
	float m_Enemy_Neu_Devx; //位置情報
	float m_Enemy_Neu_Devy;
	float m_Enemy_Neu_Dev_vx; //位置更新
	float m_Enemy_Neu_Dev_vy;

	float m_Enemy_Neu_Dev_HitSize_x;  //HitBoxサイズ
	float m_Enemy_Neu_Dev_HitSize_y;

	//死亡処理
	bool m_END_death_flg; //死亡フラグ	
};