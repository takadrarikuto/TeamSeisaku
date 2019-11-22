#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjNet :public CObj, public CBaseStatus
{
public:
	CObjNet(float x, float y);
	~CObjNet() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Barbedx; //位置情報
	float m_Barbedy;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};