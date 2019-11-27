#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBarbedWireSmall :public CObj, public CBaseStatus
{
public:
	CObjBarbedWireSmall(float x, float y);
	~CObjBarbedWireSmall() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_BarbedSx; //位置情報
	float m_BarbedSy;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};