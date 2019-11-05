#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjHeal :public CObj, public CBaseStatus
{
public:
	CObjHeal(float x, float y);
	~CObjHeal() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Healx; //位置情報
	float m_Healy;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size; 

};