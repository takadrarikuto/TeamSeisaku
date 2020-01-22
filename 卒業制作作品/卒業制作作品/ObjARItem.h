#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjARItem :public CObj, public CBaseStatus
{
public:
	CObjARItem(float x, float y);
	~CObjARItem() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_AR_Item_x; //位置情報
	float m_AR_Item_y;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

	int m_AR_num_max; //アサルトライフルの弾数回復量

};