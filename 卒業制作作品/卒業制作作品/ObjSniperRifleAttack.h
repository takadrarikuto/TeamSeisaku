#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjSniperRifleAttack :public CObj,public CBaseStatus
{
public:
	CObjSniperRifleAttack(float x, float y, float vx, float vy, float r);
	~CObjSniperRifleAttack() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	int GetSRDistance() { return m_Distance_max; } //削除距離最大値取得用

private:
	float m_SRx; //位置情報
	float m_SRy;
	float m_SRvx; //移動ベクトル
	float m_SRvy;
	float m_SRr; //画像角度調整

	int m_Distance_max; //削除距離最大値

	bool m_HitBox_Delete; //HitBox削除フラグ
};