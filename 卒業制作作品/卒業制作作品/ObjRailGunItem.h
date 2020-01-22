#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjRailGunItem :public CObj, public CBaseStatus
{
public:
	CObjRailGunItem(float x, float y);
	~CObjRailGunItem() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_RG_Item_x; //位置情報
	float m_RG_Item_y;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

	int m_RG_num_max; //レールガン回復量

};