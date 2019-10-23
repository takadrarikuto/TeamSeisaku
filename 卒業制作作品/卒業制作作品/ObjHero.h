#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjHero : public CObj, public CBaseStatus
{
public:
	CObjHero(float x, float y);
	~CObjHero() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー
	
	float GetX() { return m_x; }
	float GetY() { return m_y; }
	int GetWS() { return m_Weapon_switching; }
	int GetHP() { return m_hero_hp; }	//主人公のHPを取得

	float GetVX() { return m_vx; }
	float GetVY() { return m_vy; }

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }
	void SetVX(float vx) { m_vx = vx; }
	void SetVY(float vy) { m_vy = vy; }

private:
	float m_x; //位置更新
	float m_y;
	float m_vx; //移動ベクトル
	float m_vy;
	float m_v_max; //移動ベクトル最大値
	float m_ga_vx_max; //武器攻撃移動ベクトル最大値
	float m_ga_vy_max;

	//上下左右別
	int m_UDani_frame;	//描画フレーム
	int m_ani_time;	//アニメーションフレーム動作間隔	
	int m_LRani_frame;

	int m_damage;	//主人公が受けるダメージ用

	int m_bt; //攻撃頻度
	int m_bt_max; //攻撃頻度最大値
	int m_Weapon_switching; //武器切り替え
	bool m_Weapon_switching_flg; //武器切り替えフラグ

};