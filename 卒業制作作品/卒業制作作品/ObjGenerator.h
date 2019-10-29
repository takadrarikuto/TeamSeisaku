#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGenerator :public CObj, public CBaseStatus
{
public:
	CObjGenerator(float x, float y);
	~CObjGenerator() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー
	
	bool GetTS() { return m_Starp_flg; } //時間停止フラグ取得用

private:
	float m_Genx; //位置情報
	float m_Geny;
	float m_Genvx; //位置更新
	float m_Genvy;

	bool m_Starp_flg; //計測開始フラグ

	//上下左右別当たり判定確認フラグ
	bool m_UpHit_flg;    //上
	bool m_DownHit_flg;	 //下
	bool m_LeftHit_flg;	 //左
	bool m_LightHit_flg; //右
};