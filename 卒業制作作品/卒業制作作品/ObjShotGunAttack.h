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

	//int GetSGAPB() { return m_sga_pb; }	//残り弾数を取得

private:
	float m_gax; //位置情報
	float m_gay;
	float m_gavx; //移動ベクトル
	float m_gavy;
	float m_gar; //画像角度調整

	int Distance_max; //削除距離最大値

};