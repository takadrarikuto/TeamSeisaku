#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBarbedWire :public CObj, public CBaseStatus
{
public:
	CObjBarbedWire(float x, float y);
	~CObjBarbedWire() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Barbedx; //位置情報
	float m_Barbedy;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};