#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjAitemFont :public CObj, public CBaseStatus
{
public:
	CObjAitemFont() {};
	~CObjAitemFont() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	void SetAGF(int agf) { Aitem_Get_Font = agf; } //アイテム把握変数設定用
	void SetGunNum(int gunnum) { m_Gun_num = gunnum; } //弾表示数変数設定用
private:
	float m_Aitem_Font_x; //位置情報
	float m_Aitem_Font_y;

	int Aitem_Get_Font; //アイテム把握変数

	int m_Gun_num; //弾表示数変数

};