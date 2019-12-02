#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBarbedWireV :public CObj, public CBaseStatus
{
public:
	CObjBarbedWireV(float x, float y,bool lr_ch);
	~CObjBarbedWireV() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_BarbedVx; //位置情報
	float m_BarbedVy;
	float m_XHitbox_size; //XY当たり判定サイズ
	float m_YHitbox_size;

	bool m_BarbedV_LR_Change_flg; //左右表示切り替えフラグ
};