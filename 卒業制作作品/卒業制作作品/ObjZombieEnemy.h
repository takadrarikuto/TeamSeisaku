#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjZombieEnemy : public CObj, public CBaseStatus
{
public:
	CObjZombieEnemy(float zex, float zey);
	~CObjZombieEnemy() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	void SetAF(bool af);  //エネミー情報変更用
	float GetX() { return m_zex; } //エネミー情報取得用
	float GetY() { return m_zey; }
	int GetHP() { return m_hero_hp; }	//エネミーのHPを取得
	bool GetAF() { return m_ani_frame_flg; } //エネミー描画フレーム切り替えフラグ取得用

private:
	float m_zex; //位置更新
	float m_zey;
	float m_zevx; //移動ベクトル
	float m_zevy;
	float m_zev_max; //移動ベクトル最大値

	//上下左右別
	int m_UDani_frame;	//描画フレーム
	int m_LRani_frame;
	bool m_ani_frame_flg; 	//描画フレーム切り替えフラグ
	int m_ani_time;	//アニメーションフレーム動作間隔	

	int m_at; //攻撃頻度
	int m_at_max; //攻撃頻度最大値

};