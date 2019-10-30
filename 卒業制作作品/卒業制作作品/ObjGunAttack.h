#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGunAttack :public CObj, public CBaseStatus
{
public:
	CObjGunAttack(float x, float y,float vx, float vy,float r);
	~CObjGunAttack() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_gax; //位置情報
	float m_gay;
	float m_gavx; //移動ベクトル
	float m_gavy;
	float m_gar; //画像角度調整

	int m_Distance_max; //削除距離最大値

};