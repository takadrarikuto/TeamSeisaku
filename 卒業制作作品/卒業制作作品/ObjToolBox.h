#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjToolBox :public CObj, public CBaseStatus
{
public:
	CObjToolBox(float x, float y);
	~CObjToolBox() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Healx; //位置情報
	float m_Healy;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};