#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjRailGunAttack :public CObj, public CBaseStatus
{
public:
	CObjRailGunAttack(float x, float y, float vx, float vy, float r);
	~CObjRailGunAttack() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー
	int GetOP() { return m_Offensive_Power; }

private:
	float m_RGx; //位置情報
	float m_RGy;
	float m_RGvx; //移動ベクトル
	float m_RGvy;
	float m_RGr; //画像角度調整

	int Distance_max; //削除距離最大値
	int m_Offensive_Power; //攻撃力

};