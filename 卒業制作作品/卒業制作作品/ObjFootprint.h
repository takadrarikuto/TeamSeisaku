#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjFootprint :public CObj, public CBaseStatus
{
public:
	CObjFootprint(float x, float y,float r);
	~CObjFootprint() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

private:
	float m_Fx; //位置情報
	float m_Fy;

	int m_HitBox_x; //x当たり判定サイズ
	int m_HitBox_y; //当たり判定サイズ

	int m_ani_flame; //描画フレーム
	float m_r; //描画回転

	bool m_UDani_flg; //上下切り替え描画フラグ
	int m_Delete_time; //オブジェクト削除タイム
};