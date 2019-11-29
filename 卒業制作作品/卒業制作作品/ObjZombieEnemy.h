#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjZombieEnemy : public CObj, public CBaseStatus
{
public:
	CObjZombieEnemy(float zex, float zey, bool zeaf);
	~CObjZombieEnemy() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー
	
	float GetX() { return m_zex; } //x位置情報取得用
	float GetY() { return m_zey; } //y位置情報取得用
	int GetHP() { return m_hero_hp; }	//エネミーのHPを取得
	int GetDMG() { return m_damage; }//攻撃力を取得

private:

	float m_zex; //位置更新
	float m_zey;
	float m_zeg_x; //ゾンビ生成位置記録
	float m_zeg_y;
	float m_zevx; //移動ベクトル
	float m_zevy;
	float m_zev_max; //移動ベクトル最大値

	bool m_ze_x_flg; //移動フラグ
	bool m_ze_y_flg;

	//上下左右別当たり判定確認フラグ
	bool m_UpHit_flg;    //上
	bool m_DownHit_flg;	 //下
	bool m_LeftHit_flg;	 //左
	bool m_RightHit_flg; //右

	//上下左右別
	int m_UDani_frame;	//描画フレーム
	int m_LRani_frame;
	bool m_ani_frame_flg; 	//描画フレーム切り替えフラグ
	int m_ani_time;	//アニメーションフレーム動作間隔	

	int m_at; //攻撃頻度
	int m_at_max; //攻撃頻度最大値

	int m_damage; //ダメージ量
	int m_time_d;	//ダメージ点滅時間用
};