#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjNetV :public CObj, public CBaseStatus
{
public:
	CObjNetV(float x, float y);
	~CObjNetV() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	/*float GetNetX() { return m_Netx; } //x位置情報取得用
	float GetNetY() { return m_Nety; } //y位置情報取得用
	float GetNetHitX() { return m_XHitbox_size; } //HitBox xサイズ取得用
	float GetNetHitY() { return m_YHitbox_size; } //HitBox yサイズ取得用*/

private:
	float m_NetV_x; //位置情報
	float m_NetV_y;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

	float m_r; //角度
};