#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjARAttack :public CObj, public CBaseStatus
{
public:
	CObjARAttack(float x, float y, float vx, float vy, float r);
	~CObjARAttack() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー
	int GetOP() { return m_Offensive_Power; }

private:
	float m_ARx; //位置情報
	float m_ARy;
	float m_ARvx; //移動ベクトル
	float m_ARvy;
	float m_ARr; //画像角度調整

	int Distance_max; //削除距離最大値
	int m_Offensive_Power; //攻撃力


};