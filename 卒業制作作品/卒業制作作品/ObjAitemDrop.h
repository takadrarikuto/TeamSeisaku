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
	void SetZombieDrop(bool zombie_drop) { m_Zombie_Drop_flg = zombie_drop; } //ゾンビ
	void SetFire_LizardDrop(bool fire_lizard_drop) { m_Fire_Lizard_Drop_flg = fire_lizard_drop; } //火トカゲ
	void SetBatDrop(bool bat_drop) { Bat_Drop_flg = bat_drop; } //蝙蝠
//エネミー座標取得設定用
	void SetZombie_X(float z_x) { Z_X = z_x; } //ゾンビ
	void SetZombie_Y(float z_y) { Z_Y = z_y; }
	void SetFire_Lizard_X(float fl_x) { FL_X = fl_x; } //火トカゲ
	void SetFire_Lizard_Y(float fl_y) { FL_Y = fl_y; }
	void SetBat_X(float b_x) { B_X = b_x; } //蝙蝠
	void SetBat_Y(float b_y) { B_Y = b_y; }
private:
	bool m_Aitem_Drop_flg; //アイテムドロップフラグ
	int m_Aitem_Rand_num; //アイテムランダム選択変数

//どのエネミーからドロップするか確認するフラグ
	bool m_Zombie_Drop_flg; //ゾンビ
	bool m_Fire_Lizard_Drop_flg; //火トカゲ
	bool Bat_Drop_flg; //蝙蝠
//エネミー別で座標を記録する
	float Z_X; //ゾンビ
	float Z_Y;
	float FL_X; //火トカゲ
	float FL_Y;
	float B_X; //蝙蝠
	float B_Y;

};