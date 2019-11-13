#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjTutoWall2 :public CObj, public CBaseStatus
{
public:
	CObjTutoWall2(float x, float y);
	~CObjTutoWall2() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Wallx; //位置情報
	float m_Wally;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};