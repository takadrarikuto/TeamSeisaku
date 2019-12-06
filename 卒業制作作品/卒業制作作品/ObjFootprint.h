#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjFootprint :public CObj, public CBaseStatus
{
public:
	CObjFootprint(float x, float y, float size);
	~CObjFootprint() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_bspx; //位置情報
	float m_bspy;

	int m_ani_time; //アニメーション間隔
	int m_ani_flame; //描画フレーム

};