#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjSniperRifleItem :public CObj, public CBaseStatus
{
public:
	CObjSniperRifleItem(float x, float y);
	~CObjSniperRifleItem() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_SR_Item_x; //位置情報
	float m_SR_Item_y;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

	int m_SR_num_max; //スナイパーライフル弾数回復量

};