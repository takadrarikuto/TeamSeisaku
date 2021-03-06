#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBlood_splash :public CObj, public CBaseStatus
{
public:
	CObjBlood_splash(float x, float y, float size);
	~CObjBlood_splash() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_bspx; //位置情報
	float m_bspy;

	int m_ani_time; //アニメーション間隔
	int m_ani_flame; //描画フレーム

	float hvx; //主人公位置取得用
	float hvy; 
};