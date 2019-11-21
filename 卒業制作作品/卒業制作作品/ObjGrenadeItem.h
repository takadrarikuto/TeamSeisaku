#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGrenadeItem :public CObj, public CBaseStatus
{
public:
	CObjGrenadeItem(float x, float y);
	~CObjGrenadeItem() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_GRE_Item_x; //位置情報
	float m_GRE_Item_y;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};