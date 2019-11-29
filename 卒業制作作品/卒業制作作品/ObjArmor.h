#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjArmor :public CObj, public CBaseStatus
{
public:
	CObjArmor(float x, float y);
	~CObjArmor() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Armorx; //位置情報
	float m_Armory;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};