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

	bool GetGen() { return m_Gen_flg; } //発電機起動フラグ取得用

private:
	float m_Genx; //位置情報
	float m_Geny;
	bool m_Gen_flg; //発電機起動フラグ

};