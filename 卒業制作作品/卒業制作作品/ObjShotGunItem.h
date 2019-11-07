#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjShotGunItem :public CObj, public CBaseStatus
{
public:
	CObjShotGunItem(float x, float y);
	~CObjShotGunItem() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_SG_Item_x; //位置情報
	float m_SG_Item_y;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};