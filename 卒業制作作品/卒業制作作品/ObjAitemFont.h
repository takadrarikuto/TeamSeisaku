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
	void SetAitemNum(int Aitemnum) { m_Aitem_num = Aitemnum; } //アイテム表示数変数設定用

	void SetToolBox(bool toolbox) { m_ToolBox_flg = toolbox; } //ツールボックス画像表示フラグ設定用

	int GetA_G_F() { return Aitem_Get_Font; }	//アイテムフォントを取得

private:
	float m_Aitem_Font_x; //位置情報
	float m_Aitem_Font_y;

	int Aitem_Get_Font; //アイテム把握変数

	int m_Aitem_num; //アイテム表示数変数

	int m_Font_time; //フォント表示タイム
	bool m_Font_flg; //フォント表示フラグ

	bool m_ToolBox_flg; //ツールボックス画像表示フラグ

	wchar_t str[256]; //フォント配列

};