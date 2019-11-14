#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjTutoWall4 :public CObj, public CBaseStatus
{
public:
	CObjTutoWall4(float x, float y);
	~CObjTutoWall4() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Wallx; //位置情報
	float m_Wally;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};