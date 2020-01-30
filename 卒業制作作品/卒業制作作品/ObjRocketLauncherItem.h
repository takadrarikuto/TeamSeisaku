#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjRocketLauncherItem :public CObj, public CBaseStatus
{
public:
	CObjRocketLauncherItem(float x, float y);
	~CObjRocketLauncherItem() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_RL_Item_x; //位置情報
	float m_RL_Item_y;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

	int m_RL_num_max; //ロケットランチャー回復量

};