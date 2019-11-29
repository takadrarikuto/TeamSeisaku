#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjAitemDrop :public CObj, public CBaseStatus
{
public:
	CObjAitemDrop() {};
	~CObjAitemDrop() {};
	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetAitemDrop() { return m_Aitem_Drop_flg; } //アイテムドロップフラグ取得用
	void SetAitemDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //アイテムドロップフラグ設定用

private:
	bool m_Aitem_Drop_flg; //アイテムドロップフラグ
	int m_Aitem_Rand_num; //アイテムランダム選択変数

};