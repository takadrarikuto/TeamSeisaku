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

	void SetAitemDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //アイテムドロップフラグ設定用
//どのエネミーからドロップするか確認するフラグ設定用
	void SetZombieDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //ゾンビ
	void SetFire_BirdDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //火の鳥
	void SetFire_LizardDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //火トカゲ
	void SetBatDrop(bool aitem_drop) { m_Aitem_Drop_flg = aitem_drop; } //蝙蝠

private:
	bool m_Aitem_Drop_flg; //アイテムドロップフラグ
	int m_Aitem_Rand_num; //アイテムランダム選択変数

//どのエネミーからドロップするか確認するフラグ
	bool m_Zombie_Drop_flg; //ゾンビ
	bool m_Fire_Bird_Drop_flg; //火の鳥
	bool m_Fire_Lizard_Drop_flg; //火トカゲ
	bool Bat_Drop_flg; //蝙蝠

};