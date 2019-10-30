#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjShotGunAttack :public CObj, public CBaseStatus
{
public:
	CObjShotGunAttack(float x, float y, float vx, float vy, float r);
	~CObjShotGunAttack() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	int GetShotGunDistance() { return m_Distance_max; } //削除距離最大値取得用

private:
	float m_SGx; //位置情報
	float m_SGy;
	float m_SGvx; //移動ベクトル
	float m_SGvy;
	float m_SGr; //画像角度調整

	int m_Distance_max; //削除距離最大値

};