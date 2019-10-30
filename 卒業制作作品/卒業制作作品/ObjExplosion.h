#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjExplosion :public CObj, public CBaseStatus
{
public:
	CObjExplosion(float x, float y, float size,int Damage);
	~CObjExplosion() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	int GetEXP() { return m_Exp_Damage; } //爆発ダメージ取得用

private:
	float m_Expx; //位置情報
	float m_Expy;
	

	int m_ani_time; //アニメーション間隔
	int m_ani_flame; //描画フレーム
	int m_UDani_flame; //上下移動描画フレーム

	int m_Exp_Damage; //爆発ダメージ

};