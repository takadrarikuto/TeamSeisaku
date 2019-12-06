#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjWall4 :public CObj, public CBaseStatus
{
public:
	CObjWall4(float x, float y);
	~CObjWall4() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetX() { return m_Wallx; } //X位置情報取得用
	float GetY() { return m_Wally; } //Y位置情報取得用

private:
	float m_Wallx; //位置情報
	float m_Wally;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

};